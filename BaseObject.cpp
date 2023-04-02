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

void BaseObject::UseShader(std::string name)
{
    auto& sm = ShaderManager::GetInstance();
    if (Shader* shader = sm.Shaders[name])
    {
        sm.ActiveShader = shader;
        shader->UseShader();
    }
    else std::cout << "Tried applying false shader.\n";
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
