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
    void updateVectors();
    void UpdateCamera();

    void SetActor(Actor* actorToPossess, bool deleteCurrent = false);
    Actor* GetActor() { return mPossessedActor; }

    Camera* GetCamera();

    void Draw(GLint mModelLocation = -1) override;

    virtual void Tick(float deltaTime) override;
    virtual void OnPickup(PickupType pickup){};

protected:
    // Vectors
    QVector3D Front{};
    QVector3D Up{};
    QVector3D Right{};
    QVector3D WorldUp{};

    float Yaw{};
    float Pitch{};
    
    float mMovementSpeed;
    float mMouseSensitivity;

    Actor* mPossessedActor;

    // The current active camera
    Camera* mCamera;
};
