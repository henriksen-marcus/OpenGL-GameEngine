#pragma once

#include "Pawn.h"

class Cube;

class CubePlayer : public Pawn
{
public:
    CubePlayer();

    void Tick(float deltaTime) override;
};
