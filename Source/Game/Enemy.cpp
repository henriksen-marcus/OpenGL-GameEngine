#include "Enemy.h"
#include "Source/Engine/Pawn.h"
#include "Source/Engine/World.h"
#include "Source/Engine/Meshes/TetrahedronMesh.h"
#include <Source/Utility/Color.h>


Enemy::Enemy(const QVector3D& location) : Actor(location)
{
    mMesh = new TetrahedronMesh(this, 0.5f, 0.6f, Color::Red);
    SetCollisionComponent(0.25f);
}

void Enemy::OnCollision(Actor* otherActor)
{
    Pawn* otherPawn = dynamic_cast<Pawn*>(otherActor);
    if (otherPawn)
    {
        otherPawn->OnPickup(type);
        GetWorld()->RemoveActor(this);
    }
}
