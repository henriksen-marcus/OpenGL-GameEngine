#include "Actor.h"
#include "SceneComponent.h"
#include <iostream>

// I hate Qt

Actor::Actor(const QVector3D& location, bool init)
    : mCollisionComponent(nullptr),
      mMesh(nullptr)
{
    mLocation = location;
    if (init) Init();
}

Actor::~Actor()
{
    delete mCollisionComponent;
    delete mMesh;
    for (auto c : mComponents)
        delete c;
}

void Actor::Init()
{
}

void Actor::Draw()
{
    if (mMesh) mMesh->Draw();
}

void Actor::Tick(float deltaTime)
{
    UpdateModelMatrixQuat();
    if (mCollisionComponent)
        mCollisionComponent->Update(mLocation);
    
    if (mMesh) 
    {
    	mMesh->Tick(deltaTime);
    }

    for (auto c : mComponents)
        c->Tick(deltaTime);
}

// ---------- Translation ---------- //

const QVector3D& Actor::GetActorLocation()
{
    return mLocation;
}

void Actor::SetActorLocation(const QVector3D& location)
{
    mLocation = location;
    UpdateModelMatrixQuat();
}

void Actor::AddActorLocalOffset(const QVector3D& offset)
{
    mLocation += mForward * offset.z() + QVector3D::crossProduct(mForward, mUp) * offset.x() + mUp * offset.y();
    UpdateModelMatrixQuat();
}



// ---------- Rotation ---------- //

const QVector3D& Actor::GetActorRotation()
{
    return mRotation;
}

void Actor::SetActorRotation(const QVector3D& rotation)
{
    mRotation = rotation;
    mRotationQuat = QQuaternion::fromEulerAngles(rotation);
    UpdateModelMatrixQuat();
}

void Actor::AddActorLocalRotation(const QVector3D& offset)
{
    mRotation += offset;
    mRotationQuat = mRotationQuat * QQuaternion::fromEulerAngles(offset);
    //UpdateModelMatrixQuat();
}

void Actor::SetActorRotation(const QQuaternion& rotation)
{
    mRotationQuat = rotation;
    UpdateModelMatrixQuat();
}

void Actor::AddActorLocalRotation(const QQuaternion& offset)
{
    mRotationQuat *= offset;
    UpdateModelMatrixQuat();
}



// ---------- Scaling ---------- //

const QVector3D& Actor::GetActorScale()
{
    return mScale;
}

void Actor::SetActorScale(const QVector3D& scale)
{
    mScale = scale;
    UpdateModelMatrixQuat();
}

void Actor::AddActorLocalScale(const QVector3D& offset)
{
    mScale += offset;
    UpdateModelMatrixQuat();
}

Boundry2D* Actor::GetCollisionComponent()
{
    return mCollisionComponent;
}

void Actor::SetCollisionComponent(Boundry2D* boundry)
{
    mCollisionComponent = boundry;
}

void Actor::SetCollisionComponent(float halfLength)
{
    mCollisionComponent = new Boundry2D(QVector2D(mLocation.x(), mLocation.y()), halfLength);
}

void Actor::AddComponent(SceneComponent* component)
{
    mComponents.push_back(component);
    component->SetupAttachment(this);
}

MeshComponent* Actor::GetMesh()
{
    return mMesh;
}

void Actor::SetMesh(MeshComponent* mesh)
{
    mMesh = mesh;
}

void Actor::ClearMesh()
{
    delete mMesh;
    mMesh = nullptr;
}

void Actor::UpdateModelMatrix()
{
    print("Updt!");
    UpdateVectors();

    mMatrix.setToIdentity();
    mMatrix.translate(mLocation);

    // Pitch
    mMatrix.rotate(mRotation.x(), QVector3D(1.f, 0.f, 0.f));
    // Yaw
    mMatrix.rotate(mRotation.y(), QVector3D(0.f, 1.f, 0.f));
    // Roll
    mMatrix.rotate(mRotation.z(), QVector3D(0.f, 0.f, 1.f));

    mMatrix.scale(mScale);
}

void Actor::UpdateModelMatrixQuat()
{
    mMatrix.setToIdentity();
    mMatrix.translate(mLocation);
    mMatrix.rotate(mRotationQuat);
    mMatrix.scale(mScale);
}

void Actor::UpdateVectors()
{
    // Prevent gimball lock
    //mRotation.setX(qBound(-90.0f, mRotation.x(), 90.0f));

    mForward = QQuaternion::fromAxisAndAngle(mUp, mRotation.y()).rotatedVector(mForward);
    mForward = QQuaternion::fromAxisAndAngle(QVector3D::crossProduct(mForward, mUp), mRotation.x()).rotatedVector(mForward);
    mUp = QQuaternion::fromAxisAndAngle(mForward, mRotation.z()).rotatedVector(mUp);
    mRight = QVector3D::crossProduct(mForward, mUp).normalized();

    return;
    mForward.setX(cos(qDegreesToRadians(mYaw)) * cos(qDegreesToRadians(mPitch)));
    mForward.setY(sin(qDegreesToRadians(mPitch)));
    mForward.setZ(sin(qDegreesToRadians(mYaw)) * cos(qDegreesToRadians(mPitch)));
    mForward.normalize();
    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    mRight = QVector3D::crossProduct(mForward, mWorldUp);
    mRight.normalize();
    mUp = QVector3D::crossProduct(mRight, mForward);
    mUp.normalize();
}
