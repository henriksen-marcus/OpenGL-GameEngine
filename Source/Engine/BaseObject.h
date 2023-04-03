#pragma once

#include <QOpenGLFunctions_4_1_Core>
#include <iostream>
#include "Shader.h"
#include "DebugLogger.h"

class World;
class WorldManager;
class PlayerController;
class Shader;

class BaseObject : public QOpenGLFunctions_4_1_Core
{
public:
    BaseObject();

    static World* GetWorld();
    static PlayerController& GetPlayerController();
    static void UseShader(std::string name);
    static Shader* GetActiveShader();
    static void print(const std::string& message);
    static void print(const std::string& message, const QVector3D& vec);
    static void print(const QVector3D& vec);
};

