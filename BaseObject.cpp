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
    Shader* shader = sm.Shaders[name];
    if (shader)
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
