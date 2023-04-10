#pragma once

#include "Source/Engine/World.h"

class CameraComponent;
class LineActor;
class XYZ;
class Pawn;

class TextureScene : public World
{
public:
    TextureScene();

    void Tick(float deltaTime) override;

    LineActor* l1;
    XYZ* cross;
    Actor* mycube;
    Actor* c1, *c2;
    Pawn* player;
    CameraComponent* Cam;
    Actor* myactor;

    LineActor *x, *y, *z;
};

