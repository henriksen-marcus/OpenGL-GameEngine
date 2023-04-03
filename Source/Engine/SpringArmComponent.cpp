#include "SpringArmComponent.h"


SpringArmComponent::SpringArmComponent(Actor* parent, float cameraDistance, float cameraAngle)
	: SceneComponent(parent)
{
	mCameraOffset = GetCameraOffset(cameraDistance, cameraAngle);
}

QVector3D SpringArmComponent::GetCameraOffset(float cameraDistance, float angle)
{
	angle += 90.f;
    float x = cameraDistance * qSin(qDegreesToRadians(angle));
    float y = cameraDistance * -qCos(qDegreesToRadians(angle));
    return QVector3D(x, y, 0.f);
}

void SpringArmComponent::Tick(float deltaTime)
{
	// If the spring arm should follow the parent transform, update its location
	if (followParentTransform)
		SetWorldLocation(mParent->GetActorLocation());

	// If the spring arm should follow the parent rotation, update its rotation
	if (followParentRotation)
		SetWorldRotation(mParent->GetActorQuatRotation());

	if (mCameraComponent)
	{
		// Calculate the target location of the camera
		QVector3D targetLocation = GetWorldLocation() + GetWorldRotation().normalized() * mCameraOffset;

		// Apply spring physics to move the spring arm towards the target location
		QVector3D displacement = targetLocation - mCameraLocation;
		QVector3D springForce = displacement * mSpringStiffness;
		QVector3D dampingForce = -mCameraVelocity * mDamping;
		QVector3D acceleration = (springForce + dampingForce) / mMass;
		mCameraVelocity += acceleration * deltaTime;
		mCameraLocation += mCameraVelocity * deltaTime;

		// Update the camera component's location and rotation
		//mCameraComponent->SetWorldLocation(mCameraLocation);
		mCameraComponent->SetWorldLocation(targetLocation);
		mCameraComponent->SetWorldRotation(GetWorldRotation());
	}
}

void SpringArmComponent::SetCameraComponent(CameraComponent* cameraComponent)
{
	mCameraComponent = cameraComponent;
	mCameraLocation = cameraComponent->GetWorldLocation();
}
