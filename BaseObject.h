#pragma once

#include <QOpenGLFunctions_4_1_Core>
#include <iostream>
#include "Shader.h"

class World;
class WorldManager;
class PlayerController;
class Shader;

class BaseObject : public QOpenGLFunctions_4_1_Core
{
public:
    BaseObject();

    World* GetWorld();
    PlayerController& GetPlayerController();
    void UseShader(std::string name);
    Shader* GetActiveShader();
};

