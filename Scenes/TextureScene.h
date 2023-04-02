#pragma once

#include "World.h"

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

