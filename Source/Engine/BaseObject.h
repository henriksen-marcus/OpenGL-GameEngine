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
    static void UseShader(const std::string& name);
    static Shader* GetActiveShader();
    static void print(const std::string& message);
    static void print(const std::string& message, const QVector3D& vec);
    static void print(const QVector3D& vec);
    static void consolePrint(const std::string& message);
    static void consolePrint(const std::string& message, const QVector3D& vec);
};

template<typename Derived, typename Base>
class is_derived_from
{
    class No { };
    class Yes { No no[2]; };
    static Yes Test(Base*);
    static No Test(...);
public:
    static constexpr bool value = std::is_same<decltype(Test(std::declval<Derived*>())), Yes>::value;
};

