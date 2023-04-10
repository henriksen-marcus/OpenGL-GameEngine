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

    /**
     * \brief Set this camera as the current active
     * camera in the player controller.
     */
    void SetAsCurrent();

    float mFOV{75.f};
    bool bLookAtParent;
    void ConstrainPitch();
protected:
    void UpdateVectors() override;
    QMatrix4x4 mViewMatrix{};
};
