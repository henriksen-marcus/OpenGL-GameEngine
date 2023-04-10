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
    return QVector3D(0.f, y, x);
}

void SpringArmComponent::Tick(float deltaTime)
{
	SceneComponent::Tick(deltaTime);

	if (mCameraComponent)
	{
		// Rotate the offset vector
		QVector3D targetLocation = mWorldLocation + mWorldRotation.rotatedVector(mCameraOffset);

		if (bEnableCameraLag)
		{
			// Apply spring physics
			QVector3D displacement = targetLocation - mCameraLocation;
			QVector3D springForce = displacement * mSpringStiffness;
			QVector3D dampingForce = -mCameraVelocity * mDamping;
			QVector3D acceleration = (springForce + dampingForce) / mMass;
			mCameraVelocity += acceleration * deltaTime;
			mCameraLocation += mCameraVelocity * deltaTime;

			// Update the camera component's location and rotation
			if (mCameraComponent) mCameraComponent->SetWorldLocation(mCameraLocation);

			QVector3D cameraToPlayer = mWorldLocation - mCameraComponent->GetWorldLocation();
			cameraToPlayer.setY(0.0f); // Set the y-component to zero to ignore vertical angle

			// Calculate the angle between the camera's forward vector and the vector to the player
			float angle = qRadiansToDegrees(
				qAcos(QVector3D::dotProduct(cameraToPlayer.normalized(), QVector3D(0.f, 0.f, -1.f))));

			// Calculate the axis to rotate around (in this case, the camera's up vector)
			QVector3D rotationAxis = QVector3D::crossProduct(QVector3D(0.f, 0.f, -1.f), cameraToPlayer).normalized();

			// Create a rotation quaternion using the calculated axis and angle
			QQuaternion rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angle);
			//if (mCameraComponent) mCameraComponent->SetWorldRotation(rotation);
			// Rotate the camera's forward and up vectors using the quaternion
			QVector3D forward = rotation * QVector3D(0.f, 0.f, -1.f);
			QVector3D up = rotation * QVector3D(0.f, 1.f, 0.f);
		}
		else if (mCameraComponent) mCameraComponent->SetWorldLocation(targetLocation);
		
	}
}

void SpringArmComponent::SetCamera(CameraComponent* cameraComponent)
{
	mCameraComponent = cameraComponent;
	cameraComponent->SetWorldLocation(mWorldLocation + mCameraOffset);
}