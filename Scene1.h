#pragma once

#include "World.h"

class Plane;
class Cube;
class CubePlayer;
class XYZ;
class HealthPack;
class StaticSceneCamera;

class LineNPC;


class Scene1 : public World
{
public:
    Scene1();

    Plane* ground;
    Cube* bigCube;
    XYZ* cross;
    CubePlayer* player;
    HealthPack* pack1;
    StaticSceneCamera* sceneCamera;

    void Tick(float deltaTime, GLint mModelLocation) override;

protected:

};

