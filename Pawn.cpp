#include "Pawn.h"
#include "Cube.h"
#include "Camera.h"
#include "enums.h"

Pawn::Pawn(const QVector3D& location, bool init)
{
//    camera = new Camera(QVector3D(mLocation + QVector3D(0.f, 1.f, 1.f)));
//    camera->Pitch = -30.f;
    
    mMovementSpeed = 0.01f;
    mMouseSensitivity = 1.f;

    Front = QVector3D(0.0f, 0.0f, -1.0f);
    WorldUp = QVector3D(0.0f, 1.0f, 0.0f);
    Right = QVector3D::crossProduct(Front, WorldUp);
    Right.normalize();
    Yaw = -90.f;
    Up = WorldUp;

    mLocation = location;
    if (init) Init();
}

void Pawn::Init()
{
    
}

void Pawn::Draw()
{
    mPossessedActor->Draw();
}

void Pawn::Tick(float deltaTime)
{
    Actor::Tick(deltaTime);

    mPossessedActor->SetActorLocation(mLocation);
    mPossessedActor->SetActorRotation(mRotationQuat);
    mPossessedActor->SetActorScale(mScale);
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

    Yaw += xoffset;
    //Pitch += yoffset;

    // update Front, Right and Up Vectors using the updated Euler angles
    updateVectors();
}

void Pawn::updateVectors()
{return;
    // calculate the new Front vector
    // calculate the new Front vector
    QVector3D front;
    front.setX(cos(qDegreesToRadians(Yaw)) * cos(qDegreesToRadians(Pitch)));
    front.setY(sin(qDegreesToRadians(Pitch)));
    front.setZ(sin(qDegreesToRadians(Yaw)) * cos(qDegreesToRadians(Pitch)));
    Front = front;
    Front.normalize();
    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Right = QVector3D::crossProduct(Front, WorldUp);
    Right.normalize();
    Up = QVector3D::crossProduct(Right, Front);
    Up.normalize();
}

void Pawn::SetActor(Actor* actorToPossess, bool deleteCurrent)
{
    if (deleteCurrent && actorToPossess)
    {
        mPossessedActor = actorToPossess;
        delete mPossessedActor;
    }
}

Camera* Pawn::GetCamera()
{
    return mCamera;
}




