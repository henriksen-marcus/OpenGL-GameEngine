#pragma once

#include "Actor.h"
#include "CameraComponent.h"
#include "SceneComponent.h"

class SpringArmComponent : public SceneComponent
{
	public:
    SpringArmComponent(Actor* parent, float cameraDistance, float cameraAngle);

    void Tick(float deltaTime) override;

    static QVector3D GetCameraOffset(float cameraDistance, float angle);
    void SetCameraComponent(CameraComponent* cameraComponent);

    inline void SetSpringStiffness(float stiffness) { mSpringStiffness = stiffness; }
    inline void SetDamping(float damping) { mDamping = damping; }
    inline void SetMass(float mass) { mMass = mass; }

private:
    CameraComponent* mCameraComponent;
    QVector3D mCameraOffset;
    QVector3D mCameraLocation;
    QVector3D mCameraVelocity;

    float mSpringStiffness{500.f};
    float mDamping{10.f};
    float mMass{1.f};
};

