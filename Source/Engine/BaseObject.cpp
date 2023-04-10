#include "BaseObject.h"
#include "World.h"
#include "WorldManager.h"
#include "PlayerController.h"
#include "ShaderManager.h"

BaseObject::BaseObject()
{
}

World* BaseObject::GetWorld()
{
    return WorldManager::GetInstance().GetWorld();
}

PlayerController& BaseObject::GetPlayerController()
{
    return PlayerController::GetInstance();
}

void BaseObject::UseShader(const std::string& name)
{
    auto& sm = ShaderManager::GetInstance();
    if (Shader* shader = sm.Shaders[name])
    {
        sm.ActiveShader = shader;
        shader->UseShader();
    }
    else print("Tried applying nonexistent shader '" + name + "'.");
}

Shader* BaseObject::GetActiveShader()
{
    return ShaderManager::GetInstance().ActiveShader;
}

void BaseObject::print(const std::string& message)
{
	DebugLogger::GetInstance().Print(message);
}

void BaseObject::print(const std::string& message, const QVector3D& vec)
{
    print(message + " " + std::to_string(vec.x()) + " " + std::to_string(vec.y()) + " " + std::to_string(vec.z()));
}

void BaseObject::print(const QVector3D& vec)
{
    print(std::to_string(vec.x()) + " " + std::to_string(vec.y()) + " " + std::to_string(vec.z()));
}

void BaseObject::consolePrint(const std::string& message)
{
    std::cout << message << std::endl;
}

void BaseObject::consolePrint(const std::string& message, const QVector3D& vec)
{
    std::cout << message << " " << vec.x() << " " << vec.y() << " " << vec.z() << std::endl;
}
