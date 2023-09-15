#include "LightSwitch.h"
#include "Source/Engine/Pawn.h"
#include "Source/Engine/World.h"
#include <Source/Utility/Color.h>
#include "Source/Engine/Meshes/CubeMesh.h"


LightSwitch::LightSwitch(const QVector3D& location) : Actor(location)
{
    mMesh = new CubeMesh(this, 0.3f, Color::Pink);
    SetCollisionComponent(0.15f);
}

void LightSwitch::OnCollision(Actor* otherActor)
{
    Pawn* otherPawn = dynamic_cast<Pawn*>(otherActor);
    if (otherPawn)
    {
        otherPawn->OnPickup(type);
    }
}
