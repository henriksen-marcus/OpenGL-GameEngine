#pragma once

#include <QOpenGLFunctions_4_1_Core>

class World;
class WorldManager;
class PlayerController;

class BaseObject : public QOpenGLFunctions_4_1_Core
{
public:
    BaseObject();

    World* GetWorld();
    PlayerController& GetPlayerController();
    void UseShader(std::string name);
};

