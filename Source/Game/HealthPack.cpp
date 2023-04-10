#include "HealthPack.h"
#include "Source/Engine/Pawn.h"
#include "Source/Engine/World.h"
#include "Source/Engine/Meshes/CubeMesh.h"


HealthPack::HealthPack(const QVector3D& location) : Actor(location)
{
    mMesh = new CubeMesh(this, 0.2f, QVector3D(1.f,0.1f,0.1f));
    SetCollisionComponent(0.1f);
}

void HealthPack::OnCollision(Actor* otherActor)
{
    Pawn* otherPawn = dynamic_cast<Pawn*>(otherActor);
    if (otherPawn)
    {
        otherPawn->OnPickup(type);
        GetWorld()->RemoveActor(this);
    }
}
