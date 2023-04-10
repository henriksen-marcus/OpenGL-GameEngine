#pragma once

#include "Actor.h"
#include "enums.h"

class Camera;

class Pawn : public Actor
{
public:
    Pawn(const QVector3D& location = QVector3D());

    void Init() override;

    virtual void ProcessKeyboard(Movement direction);
    virtual void ProcessMouseMovement(float xoffset, float yoffset);
    virtual void ProcessMouseScroll(float yoffset);

    void SetMovementSpeed(float speed);
    /**
     * \brief Set this pawn as the current active pawn
     * in the player controller.
     */
    virtual void SetAsCurrent();

    void Draw() override;

    void Tick(float deltaTime) override;
    virtual void OnPickup(PickupType pickup){};

protected:
    float mMovementSpeed;
    float mMouseSensitivity;
    QVector3D mTranslationQuery;
    QVector3D mRotationQuery;
};
