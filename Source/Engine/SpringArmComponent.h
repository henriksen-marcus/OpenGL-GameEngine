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
    void SetCamera(CameraComponent* cameraComponent);
    QVector3D GetSocketLocation() const { return mWorldLocation + mCameraOffset; }

    inline void SetSpringStiffness(float stiffness) { mSpringStiffness = stiffness; }
    inline void SetDamping(float damping) { mDamping = damping; }
    inline void SetMass(float mass) { mMass = mass; }

	bool bEnableCameraLag{true};

private:
    CameraComponent* mCameraComponent;
    QVector3D mCameraOffset;
    QVector3D mCameraLocation;
    QVector3D mCameraVelocity;

    float mSpringStiffness{200.f};
    float mDamping{30.f};
    float mMass{2.f};
};

