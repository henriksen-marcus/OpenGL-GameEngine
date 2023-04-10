#pragma once

#include "Source/Engine/Actor.h"

class Plane;
class CameraComponent;

class House : public Actor
{
public:
    House(const QVector3D& location);

    void Draw() override;
    void Tick(float deltaTime) override;
    void OnCollision(Actor* otherActor) override;

    CameraComponent* mainCam;
    CameraComponent* houseCam;

protected:
    bool isColliding = false;
    Plane* mDoor;

    Plane* backWall;
    Plane* bottom;
    Plane* top;
    Plane* leftWall;
    Plane* rightWall;

    Plane* leftOfDoor;
    Plane* rightOfDoor;
};


