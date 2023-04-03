#pragma once

#include "Source/Engine/World.h"

class LineActor;
class XYZ;

class TextureScene : public World
{
public:
    TextureScene();

    void Tick(float deltaTime) override;

    LineActor* l1;
    XYZ* cross;
    Actor* mycube;
};

