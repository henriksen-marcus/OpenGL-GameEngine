#include "World.h"
#include "Actor.h"
#include <QElapsedTimer>
#include "PausableTimer.h"
#include "Quadtree.h"

World::World()
{
    mRenderer = new Renderer();
    mQuadtree = new Quadtree(new Boundry2D(QVector2D(), 100.f), 0.f);
    isPaused = false;


    worldTimer = new PauseableTimer();
    worldUnpausedTimer = new QElapsedTimer();
    worldTimer->start();
    worldUnpausedTimer->start();
}

void World::Tick(float deltaTime, GLint mModelLocation)
{
    if (isPaused) return;
    mDeltaTime = deltaTime;

    // Check each object in the world for collision
    for (auto actor : mActors)
    {
        Boundry2D* coll = actor->GetCollisionComponent();
        if (!coll) continue; // Actor has no collision

        std::vector<Actor*> found;
        mQuadtree->Query(found, coll);
        if (!found.empty())
        {
            actor->OnCollision(found.front());
            for (auto otherActor : found)
            {
                otherActor->OnCollision(actor);
            }
        }
    }

    mRenderer->DrawObjects(mModelLocation, deltaTime);
}

bool World::ContainsActor(Actor* actor)
{
    // TODO: this is a complicated process..
    return false;
}

bool World::ContainsActor(const std::string& name)
{
    return mRenderer->Find(name);
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

void World::RemoveActor(Actor* actor)
{
    for (int i{}; i < mActors.size(); i++)
    {
        if (mActors[i] == actor) mActors.erase(mActors.begin() + i);
    }
}
