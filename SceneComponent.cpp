#include "SceneComponent.h"
#include "VisualObject.h"
#include "Actor.h"

SceneComponent::SceneComponent(Actor* parent)
    : mParent(parent)
{
}

void SceneComponent::SetRelativeLocation(const QVector3D& location)
{
    followParentTransform = true;
    mRelativeLocation = location;
}

void SceneComponent::AddRelativeLocation(const QVector3D& offset)
{
    followParentTransform = true;
    mRelativeLocation += offset;
}

void SceneComponent::SetWorldLocation(const QVector3D& location)
{
    followParentTransform = false;
    mWorldLocation = location;
}

void SceneComponent::AddWorldOffset(const QVector3D& offset)
{
    followParentTransform = false;
    mWorldLocation += offset;
}

void SceneComponent::SetRelativeRotation(const QQuaternion& rotation)
{
    followParentRotation = true;
    mRelativeRotation = rotation;
}

void SceneComponent::AddRelativeRotation(const QQuaternion& offset)
{
    followParentRotation = true;
    mRelativeRotation += offset;
}

void SceneComponent::SetWorldRotation(const QQuaternion& rotation)
{
    followParentRotation = false;
    mWorldRotation = rotation;
}

void SceneComponent::AddWorldRotation(const QQuaternion& offset)
{
    followParentRotation = false;
    mWorldRotation += offset;
}

void SceneComponent::SetActorScale(const QVector3D& scale)
{
    mScale = scale;
}

void SceneComponent::AddActorLocalScale(const QVector3D& offset)
{
    mScale += offset;
}

void SceneComponent::Tick(float deltaTime)
{
    if (followParentTransform)
        SetWorldLocation(mParent->GetActorLocation() + GetRelativeLocation());
    if (followParentRotation)
        SetWorldRotation(mParent->GetActorQuatRotation() + GetRelativeRotation());
}
