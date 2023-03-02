#include "World.h"
#include "Actor.h"
#include <QElapsedTimer>
#include "PausableTimer.h"

World::World()
{
    worldTimer->start();
    worldUnpausedTimer->start();
}

void World::Pause(bool shouldPause)
{
    isPaused = shouldPause;
    if (isPaused) worldTimer->pause();
    else worldTimer->resume();
}

float World::GetTimeSeconds()
{
    return worldTimer->elapsed();
}

float World::GetUnpausedTimeSeconds()
{
    return worldUnpausedTimer->elapsed();
}
