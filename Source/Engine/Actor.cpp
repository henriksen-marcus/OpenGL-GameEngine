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
    UpdateVectors();

    if (mCollisionComponent)
        mCollisionComponent->UpdateLocation(mLocation);
    
    if (mMesh) 
    {
        mMesh->Tick(deltaTime);
    }

    for (auto c : mComponents)
        c->Tick(deltaTime);
}

// ---------- Translation ---------- //

const QVector3D& Actor::GetActorLocation() const
{
    return mLocation;
}

QVector2D Actor::GetActorLocation2D() const
{
    return QVector2D(mLocation.x(), mLocation.z());
}

void Actor::SetActorLocation(const QVector3D& location)
{
    mLocation = location;
}

void Actor::AddActorLocalOffset(const QVector3D& offset)
{
    mLocation += mRotationQuat.rotatedVector(offset);
}

void Actor::AddActorWorldOffset(const QVector3D& offset)
{
    mLocation += offset;
}


// ---------- Rotation ---------- //

const QVector3D& Actor::GetActorRotation()
{
    return mRotationQuat.toEulerAngles();
}

void Actor::SetActorRotation(const QVector3D& rotation)
{
    mRotation = rotation;
    mRotationQuat = QQuaternion::fromEulerAngles(rotation);
}

void Actor::AddActorLocalRotation(const QVector3D& offset)
{
    mRotation += offset;
    mRotationQuat *= QQuaternion::fromEulerAngles(offset);
}

void Actor::SetActorRotation(const QQuaternion& rotation)
{
    mRotationQuat = rotation;
}

void Actor::AddActorLocalRotation(const QQuaternion& offset)
{
    mRotationQuat *= offset;
}



// ---------- Scaling ---------- //

const QVector3D& Actor::GetActorScale()
{
    return mScale;
}

void Actor::SetActorScale(const QVector3D& scale)
{
    mScale = scale;
    UpdateCollisionScale();
    //UpdateModelMatrixQuat();
}

void Actor::AddActorLocalScale(const QVector3D& offset)
{
    mScale += offset;
    UpdateCollisionScale();
    //UpdateModelMatrixQuat();
}

void Actor::UpdateCollisionScale()
{
    if (mCollisionComponent) mCollisionComponent->UpdateScale(mScale);
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
    mesh->SetupAttachment(this);
}

void Actor::ClearMesh()
{
    delete mMesh;
    mMesh = nullptr;
}

void Actor::UpdateModelMatrix()
{
    return;
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
    mForward = mRotationQuat.rotatedVector(QVector3D(0.f, 0.f, -1.f));
    mUp = mRotationQuat.rotatedVector(QVector3D(0.f, 1.f, 0.f));
    mForward.normalize();
    mUp.normalize();
}