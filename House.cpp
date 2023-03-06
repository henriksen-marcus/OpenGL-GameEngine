#include "House.h"
#include "Plane.h"
#include "Pawn.h"
#include "PlayerController.h"
#include "CameraComponent.h"

House::House(const QVector3D& location)
{
    mLocation = location;

    float size = 1.f;
    QVector3D color(1.f, 1.f, 1.f);

    mDoor = new Plane(mLocation + QVector3D(0.f, 0.f, size/2.f), size/3.f, size, QVector3D(0.2f, 0.7f, 0.2f));
    mDoor->AddActorLocalRotation(QVector3D(90.f, 0.f, 0.f));

    backWall = new Plane(mLocation + QVector3D(0.f, 0.f, -size/2.f), size, size);
    backWall->AddActorLocalRotation(QVector3D(90.f, 0.f, 0.f));
    bottom = new Plane(mLocation + QVector3D(0.f, -size/2.f, 0.f), size, size, QVector3D(0.f, 0.5f, 0.5f));
    top = new Plane(mLocation + QVector3D(0.f, size/2.f, 0.f), size, size);
    leftWall = new Plane(mLocation + QVector3D(-size/2.f, 0.f, 0.f), size, size);
    leftWall->AddActorLocalRotation(QVector3D(0.f, 0.f, 90.f));
    rightWall = new Plane(mLocation + QVector3D(size/2.f, 0.f, 0.f), size, size);
    rightWall->AddActorLocalRotation(QVector3D(0.f, 0.f, 90.f));
    leftOfDoor = new Plane(mLocation + QVector3D(-size/3.f, 0.f, size/2.f), size/3.f, size, QVector3D(0.5f, 0.7f, 0.f));
    leftOfDoor->AddActorLocalRotation(QVector3D(90.f, 0.f, 0.f));
    rightOfDoor = new Plane(mLocation + QVector3D(size/3.f, 0.f, size/2.f), size/3.f, size, QVector3D(0.5f, 0.7f, 0.f));
    rightOfDoor->AddActorLocalRotation(QVector3D(90.f, 0.f, 0.f));

    SetCollisionComponent(0.5f);
    mCollisionComponent->Update(mLocation);
    //Init();
}

void House::Draw(GLint mModelLocation)
{
    backWall->Draw(mModelLocation);
    bottom->Draw(mModelLocation);
    top->Draw(mModelLocation);
    leftWall->Draw(mModelLocation);
    rightWall->Draw(mModelLocation);
    leftOfDoor->Draw(mModelLocation);
    rightOfDoor->Draw(mModelLocation);
    mDoor->Draw(mModelLocation);
}

void House::Tick(float deltaTime)
{
    Actor::Tick(deltaTime);
    if (isColliding)
    {
        GetPlayerController().SetCurrentCamera(houseCam);
        isColliding = false;
    }
    else GetPlayerController().SetCurrentCamera(mainCam);
}

void House::OnCollision(Actor* otherActor)
{
    Actor::OnCollision(otherActor);

    if (dynamic_cast<Pawn*>(otherActor))
    {
        isColliding = true;
        static bool hasMoved;

        if (!hasMoved)
        {
            hasMoved = true;
            mDoor->AddActorLocalOffset(QVector3D(0.f, 1.f, 0.f));
        }

    }
}
