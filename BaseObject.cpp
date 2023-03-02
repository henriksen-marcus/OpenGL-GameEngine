#include "BaseObject.h"
#include "World.h"
#include "WorldManager.h"

BaseObject::BaseObject()
{
}

World* BaseObject::GetWorld()
{
    return WorldManager::GetInstance().GetWorld();
}
