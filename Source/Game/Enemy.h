#pragma once

#include "Source/Engine/Actor.h"
#include "Source/Engine/enums.h"

class Enemy : public Actor
{
public:
    Enemy(const QVector3D& location);
    void OnCollision(Actor* otherActor) override;

private:
    PickupType type = PickupType::Damage;
};
