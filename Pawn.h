#pragma once

#include "Actor.h"
#include "enums.h"

class Pawn : public Actor
{
public:
    Pawn(const QVector3D& location = QVector3D(), bool init = false);

    void Init() override;

    void ProcessKeyboard(enum Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset);
    void updateVectors();
    void UpdateCamera();

    void SetActor(Actor* actorToPossess, bool deleteCurrent = false);
    Actor* GetActor() { return posessedActor; }

    virtual void Update();

    void Draw(GLint mModelLocation = -1) override;

protected:
    // Vectors
    QVector3D Front{};
    QVector3D Up{};
    QVector3D Right{};
    QVector3D WorldUp{};

    float Yaw{};
    float Pitch{};
    
    float movementSpeed;
    float mouseSensitivity;

    Actor* posessedActor;
};
