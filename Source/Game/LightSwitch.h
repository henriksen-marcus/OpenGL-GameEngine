#pragma once

#include "Source/Engine/Actor.h"
#include "Source/Engine/enums.h"

class LightSwitch : public Actor
{
public:
    LightSwitch(const QVector3D& location);
    void OnCollision(Actor* otherActor) override;

private:
    PickupType type = PickupType::Switch;
};
