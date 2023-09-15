#include "HealthPack.h"
#include "Source/Engine/Pawn.h"
#include "Source/Engine/World.h"
#include "Source/Engine/Meshes/SphereMesh.h"


HealthPack::HealthPack(const QVector3D& location) : Actor(location)
{
    mMesh = new SphereMesh(this, 0.3f, QVector3D(0.1f,0.8f,0.1f));
    SetCollisionComponent(0.15f);
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
