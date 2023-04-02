#pragma once

#include "Actor.h"
#include "enums.h"

class Camera;

class Pawn : public Actor
{
public:
    Pawn(const QVector3D& location = QVector3D(), bool init = false);

    void Init() override;

    void ProcessKeyboard(Movement direction);
    void ProcessMouseMovement(float xoffset, float yoffset);
    void UpdateCamera();

    void Draw() override;

    virtual void Tick(float deltaTime) override;
    virtual void OnPickup(PickupType pickup){};

protected:
    float mMovementSpeed;
    float mMouseSensitivity;
};
