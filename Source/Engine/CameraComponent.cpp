#include "CameraComponent.h"
#include "Actor.h"
#include "PlayerController.h"

CameraComponent::CameraComponent(Actor* parent)
    : SceneComponent(parent),
	  bLookAtParent(false)
{
    //mWorldRotation = QQuaternion::fromEulerAngles(QVector3D(0.f, -90.f, 0.f));
    //camRotation = QVector3D(0.f, -90.f, 0.f);
    mViewMatrix.setToIdentity();
    mForward = QVector3D(0.f, 0.f, -1.f);
    UpdateVectors();
}

QMatrix4x4& CameraComponent::GetViewMatrix()
{
    mViewMatrix.setToIdentity();
    if (bLookAtParent)
    {
        mViewMatrix.lookAt(mWorldLocation, mParent->GetActorLocation(), mUp);
    }
	else mViewMatrix.lookAt(mWorldLocation, mWorldLocation + mForward, mUp);
    return mViewMatrix;
}

void CameraComponent::Tick(float deltaTime)
{
    SceneComponent::Tick(deltaTime);
    ConstrainPitch();
}

void CameraComponent::ConstrainPitch()
{
    // Constrain pitch
    auto rot = mWorldRotation.toEulerAngles();
    rot.setX(qBound(-80.f, rot.x(), 80.f));
    mWorldRotation = QQuaternion::fromEulerAngles(rot);
}

void CameraComponent::UpdateVectors()
{
    mForward = mWorldRotation.rotatedVector(QVector3D(0.f, 0.f, -1.f));
    mForward.normalize();
    /*mUp = mWorldRotation.rotatedVector(QVector3D(0.f, 1.f, 0.f));
    mUp.normalize();*/
    auto right = QVector3D::crossProduct(mForward, mWorldUp).normalized();
    mUp = QVector3D::crossProduct(right, mForward).normalized();
    auto d = mWorldRotation.toEulerAngles();
    d.setZ(0.f);
    mWorldRotation = QQuaternion::fromEulerAngles(d);
}

void CameraComponent::SetAsCurrent()
{
    GetPlayerController().SetCurrentCamera(this);
}
