#include "CameraComponent.h"

CameraComponent::CameraComponent(Actor* parent)
    : SceneComponent(parent)
{
    UpdateCameraVectors();
}

QMatrix4x4& CameraComponent::GetViewMatrix()
{
    mLookAtMatrix.setToIdentity();
    mLookAtMatrix.lookAt(mWorldLocation, mWorldLocation + mForward, mUp);
    return mLookAtMatrix;
}

void CameraComponent::Tick(float deltaTime)
{
    SceneComponent::Tick(deltaTime);
    mPitch = qBound(-89.9f, mPitch, 89.9f);
    UpdateCameraVectors();
}

void CameraComponent::UpdateCameraVectors()
{
    // Calculate the new front vector
    QVector3D front;
    front.setX(cos(qDegreesToRadians(mYaw)) * cos(qDegreesToRadians(mPitch)));
    front.setY(sin(qDegreesToRadians(mPitch)));
    front.setZ(sin(qDegreesToRadians(mYaw)) * cos(qDegreesToRadians(mPitch)));
    mForward = front.normalized();
    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    mRight = QVector3D::crossProduct(mForward, mWorldUp).normalized();
    mUp = QVector3D::crossProduct(mRight, mForward).normalized();
}
