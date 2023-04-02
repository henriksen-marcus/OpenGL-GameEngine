#include "Pawn.h"
#include "Camera.h"
#include "enums.h"

Pawn::Pawn(const QVector3D& location, bool init)
{
//    camera = new Camera(QVector3D(mLocation + QVector3D(0.f, 1.f, 1.f)));
//    camera->Pitch = -30.f;
    
    mMovementSpeed = 0.01f;
    mMouseSensitivity = 1.f;

    mLocation = location;
    if (init) Init();
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
}

void Pawn::ProcessKeyboard(Movement direction)
{
    switch (direction)
    {
    case Movement::FORWARD:
        AddActorLocalOffset(QVector3D(0.f, 0.f, -mMovementSpeed));
        break;
    case Movement::BACKWARD:
        AddActorLocalOffset(QVector3D(0.f, 0.f, mMovementSpeed));
        break;
    case Movement::LEFT:
        AddActorLocalOffset(QVector3D(mMovementSpeed, 0.f, 0.f));
        break;
    case Movement::RIGHT:
        AddActorLocalOffset(QVector3D(-mMovementSpeed, 0.f, 0.f));
        print("RIGHT");
        break;
    case Movement::UP:
        //mLocation += Up * velocity;
        break;
    case Movement::DOWN:
        //mLocation -= Up * velocity;
        break;
    case Movement::JUMP:
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




