#include "FlyingCamera.h"
#include "Source/Engine/CameraComponent.h"

FlyingCamera::FlyingCamera(const QVector3D& location)
	: Pawn(location)
{
	mCamera = new CameraComponent(this);
	mCamera->mFOV = 75.f;
	mCamera->SetFollowParent(false);
	mComponents.push_back(mCamera);
	mMouseSensitivity = 0.05f;
	mMovementSpeed = 0.06f;
}

void FlyingCamera::ProcessKeyboard(Movement direction)
{
	switch (direction)
	{
	case Movement::FORWARD:
		AddActorWorldOffset(mCamera->GetForwardVector() * mMovementSpeed);
		break;
	case Movement::BACKWARD:
		AddActorWorldOffset(-mCamera->GetForwardVector() * mMovementSpeed);
		break;
	case Movement::LEFT:
		AddActorWorldOffset(-mCamera->GetRightVector() * mMovementSpeed);
		break;
	case Movement::RIGHT:
		AddActorWorldOffset(mCamera->GetRightVector() * mMovementSpeed);
		break;
	case Movement::UP:
		AddActorWorldOffset(mWorldUp * mMovementSpeed);
		break;
	case Movement::DOWN:
		AddActorWorldOffset(-mWorldUp * mMovementSpeed);
		break;
	}
}

void FlyingCamera::ProcessMouseMovement(float xoffset, float yoffset)
{
	mCamera->AddWorldRotation(QVector3D(yoffset*mMouseSensitivity, -xoffset*mMouseSensitivity, 0.f));
}

void FlyingCamera::Tick(float deltaTime)
{
	Pawn::Tick(deltaTime);
	mCamera->SetWorldLocation(mLocation);
}
