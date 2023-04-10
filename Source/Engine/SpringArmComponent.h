#pragma once

#include "Actor.h"
#include "SceneComponent.h"

class SpringArmComponent : public SceneComponent
{
	public:
    SpringArmComponent(Actor* parent, float cameraDistance, float cameraAngle);
    void Tick(float deltaTime) override;

    static QVector3D GetOffset(float cameraDistance, float angle);
    void SetAttachment(SceneComponent* cameraComponent);
    QVector3D GetSocketLocation() const { return mWorldLocation + mComponentOffset; }

    inline void SetSpringStiffness(float stiffness) { mSpringStiffness = stiffness; }
    inline void SetDamping(float damping) { mDamping = damping; }
    inline void SetMass(float mass) { mMass = mass; }

	bool bEnableCameraLag{true};

private:
    SceneComponent* mAttachedComponent;
    QVector3D mComponentOffset;
    QVector3D mComponentLocation;
    QVector3D mComponentVelocity;

    float mSpringStiffness{200.f};
    float mDamping{30.f};
    float mMass{2.f};
};

