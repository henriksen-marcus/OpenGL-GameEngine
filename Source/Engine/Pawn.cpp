#include "Pawn.h"
#include "CameraComponent.h"
#include "enums.h"
#include "PlayerController.h"

Pawn::Pawn(const QVector3D& location)
	: Actor(location)
{
    mMovementSpeed = 0.03f;
    mMouseSensitivity = 0.2f;
}

void Pawn::Init()
{
    
}

void Pawn::Draw()
{
    Actor::Draw();
}

void Pawn::Tick(float deltaTime)
{
    Actor::Tick(deltaTime);

    AddActorWorldOffset(mTranslationQuery * deltaTime);
    AddActorLocalRotation(mRotationQuery * deltaTime);
    mTranslationQuery = QVector3D();
    mRotationQuery = QVector3D();
}

void Pawn::ProcessKeyboard(const Movement direction)
{
    switch (direction)
    {
    case Movement::FORWARD:
        //AddActorWorldOffset(mForward*mMovementSpeed);
        mTranslationQuery += mForward * mMovementSpeed;
        break;
    case Movement::BACKWARD:
        //AddActorWorldOffset(-mForward * mMovementSpeed);
        mTranslationQuery += -mForward * mMovementSpeed;
        break;
    case Movement::LEFT:
        //AddActorWorldOffset(-GetActorRightVector() * mMovementSpeed);
        mTranslationQuery += -GetActorRightVector() * mMovementSpeed;
        break;
    case Movement::RIGHT:
        //AddActorWorldOffset(GetActorRightVector() * mMovementSpeed);
        mTranslationQuery += GetActorRightVector() * mMovementSpeed;
        break;
    case Movement::UP:
        //AddActorWorldOffset(mWorldUp * mMovementSpeed);
        mTranslationQuery += mWorldUp * mMovementSpeed;
        break;
    case Movement::DOWN:
        //AddActorWorldOffset(-mWorldUp * mMovementSpeed);
        mTranslationQuery += -mWorldUp * mMovementSpeed;
        break;
    case Movement::JUMP:
        break;
	case ROTATE_LEFT:
        //AddActorLocalRotation(QVector3D(0.f, 1.f, 0.f));
        mRotationQuery += QVector3D(0.f, 1.f, 0.f);
        break;
	case ROTATE_RIGHT:
        //AddActorLocalRotation(QVector3D(0.f, -1.f, 0.f));
        mRotationQuery += QVector3D(0.f, -1.f, 0.f);
        break;
    }
}

void Pawn::ProcessMouseMovement(float xoffset, float yoffset)
{
    return;
    xoffset *= mMouseSensitivity;
    //yoffset *= mouseSensitivity;

    //Yaw += xoffset;
    //Pitch += yoffset;

    // update Front, Right and Up Vectors using the updated Euler angles
}

void Pawn::ProcessMouseScroll(float yoffset)
{
    mMovementSpeed = qBound(0.001f, mMovementSpeed + yoffset * 0.005f, 20.f);
}

void Pawn::SetMovementSpeed(float speed)
{
    mMovementSpeed = speed;
}

void Pawn::SetAsCurrent()
{
    GetPlayerController().SetCurrentPossessed(this);
}




