#include "CubePlayer.h"

CubePlayer::CubePlayer()
{
    mMovementSpeed *= 3.f;
    SetCollisionComponent(0.1f);
}

void CubePlayer::Tick(float deltaTime)
{
    Pawn::Tick(deltaTime);
}

