#pragma once

#include "SceneComponent.h"
#include "enums.h"
#include "qmatrix4x4.h"

class CameraComponent : public SceneComponent
{
public:
    CameraComponent(Actor* parent);
    QMatrix4x4& GetViewMatrix();
    void Tick(float deltaTime) override;

    float mYaw{-90.f};
    float mPitch{0.f};
    float mFOV{75.f};

protected:
    virtual void UpdateCameraVectors();

    QMatrix4x4 mLookAtMatrix{};
};
