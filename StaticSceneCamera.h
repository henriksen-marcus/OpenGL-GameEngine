#pragma once

#include "Actor.h"

class CameraComponent;

/* Actor for holding the two cameras for Scene1. */
class StaticSceneCamera : public Actor
{
public:
    StaticSceneCamera();
    CameraComponent* GetCurrentCamera();
    CameraComponent* SwapCamera();
    void Tick(float deltaTime) override;

protected:
    CameraComponent* activeCamera;
    CameraComponent* camera1;
    CameraComponent* camera2;
};

