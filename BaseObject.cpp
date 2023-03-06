#include "BaseObject.h"
#include "World.h"
#include "WorldManager.h"
#include "PlayerController.h"

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
