#pragma once

#include "Actor.h"
#include "enums.h"

class HealthPack : public Actor
{
public:
    HealthPack(const QVector3D& location);
    void OnCollision(Actor* otherActor) override;

private:
    PickupType type = PickupType::Health;
};
