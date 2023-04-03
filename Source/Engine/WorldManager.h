#pragma once

#include "BaseObject.h"
#include "World.h"

class WorldManager : public BaseObject
{
public:
    static WorldManager& GetInstance()
    {
        static WorldManager instance;
        return instance;
    }

    World* GetWorld() { return mCurrentWorld; }

    void SetWorld(World* newWorld){ mCurrentWorld = newWorld; }

private:
    WorldManager(){}
    ~WorldManager(){}

    WorldManager(const WorldManager&) = delete;
    WorldManager& operator = (const WorldManager&) = delete;

    World* mCurrentWorld;
};
