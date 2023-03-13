#include "BaseObject.h"
#include "World.h"
#include "WorldManager.h"
#include "PlayerController.h"
#include "ShaderManager.h"
#include "Shader.h"

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
    Shader* shader = ShaderManager::GetInstance().Shaders[name];
    if (shader) shader->UseShader();
}
