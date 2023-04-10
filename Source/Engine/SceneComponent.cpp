#include "SceneComponent.h"
#include "Actor.h"

SceneComponent::SceneComponent(Actor* parent) :
	followParentTransform(true),
	followParentRotation(true),
	followParentScale(true),
	mParent(parent)
{
}

void SceneComponent::SetupAttachment(Actor* parent)
{
	mParent = parent;
}

void SceneComponent::SetFollowParent(bool follow)
{
    followParentTransform = follow;
    followParentRotation = follow;
    followParentRotation = follow;
}

void SceneComponent::SetRelativeLocation(const QVector3D& location)
{
    mRelativeLocation = location;
}

void SceneComponent::AddRelativeLocation(const QVector3D& offset)
{
    mRelativeLocation += offset;
}

void SceneComponent::SetWorldLocation(const QVector3D& location)
{
    mWorldLocation = location;
}

void SceneComponent::AddWorldOffset(const QVector3D& offset)
{
    mWorldLocation += offset;
}

void SceneComponent::SetRelativeRotation(const QQuaternion& rotation)
{
    mRelativeRotation = rotation;
}

void SceneComponent::AddRelativeRotation(const QQuaternion& offset)
{
    mRelativeRotation += offset;
}

void SceneComponent::SetWorldRotation(const QQuaternion& rotation)
{
    mWorldRotation = rotation;
}

void SceneComponent::AddWorldRotation(const QQuaternion& offset)
{
    mWorldRotation *= offset;
}

void SceneComponent::AddWorldRotation(const QVector3D& offset)
{
    mWorldRotation *= QQuaternion::fromEulerAngles(offset);
}

void SceneComponent::SetWorldScale(const QVector3D& scale)
{
    mScale = scale;
}

void SceneComponent::AddWorldScale(const QVector3D& offset)
{
    mScale += offset;
}

void SceneComponent::Tick(float deltaTime)
{
    if (followParentTransform)
	    SetWorldLocation(mParent->GetActorLocation() + mParent->GetActorQuatRotation().rotatedVector(mRelativeLocation));

    if (followParentRotation)
        SetWorldRotation(mParent->GetActorQuatRotation() * mRelativeRotation);

    if (followParentScale)
        SetWorldScale(mParent->GetActorScale());

    UpdateModelMatrixQuat();
    UpdateVectors();
}

void SceneComponent::UpdateModelMatrixQuat()
{
    mMatrix.setToIdentity();
	mMatrix.translate(mWorldLocation);
	mMatrix.rotate(mWorldRotation);
	mMatrix.scale(mScale);
}

void SceneComponent::UpdateModelMatrix()
{
    //UpdateVectors();

    mMatrix.setToIdentity();
    mMatrix.translate(mWorldLocation);

    // Pitch
    mMatrix.rotate(mWorldRotation.x(), QVector3D(1.f, 0.f, 0.f));
    // Yaw
    mMatrix.rotate(mWorldRotation.y(), QVector3D(0.f, 1.f, 0.f));
    // Roll
    mMatrix.rotate(mWorldRotation.z(), QVector3D(0.f, 0.f, 1.f));

    mMatrix.scale(mScale);
}

void SceneComponent::UpdateVectors()
{
    mForward = mWorldRotation.rotatedVector(QVector3D(0.f, 0.f, -1.f));
    mUp = mWorldRotation.rotatedVector(QVector3D(0.f, 1.f, 0.f));
}
