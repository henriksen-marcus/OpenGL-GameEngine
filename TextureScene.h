#pragma once

#include "World.h"

class TextureScene : public World
{
public:
    TextureScene();

    void Tick(float deltaTime) override;
};

