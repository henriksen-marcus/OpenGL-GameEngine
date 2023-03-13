#include "World.h"
#include "Actor.h"
#include <QElapsedTimer>
#include "PausableTimer.h"
#include "Quadtree.h"
#include <iostream>
#include "Cube.h"

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

    mQuadtree->UpdateTree(mActors);

//    for (auto a : mActors)
//    {
//        if (a->GetCollisionComponent())
//        {
//            auto c = a->GetCollisionComponent();
//            //printf("Collision pos: %f, %f\n", c->mLocation.x(), c->mLocation.y());
//            //std::cout << "Collision pos: " << c->mLocation.x() << "," <<  c->mLocation.y() << "\n";
//            //std::cout << "Actor pos: " << a->GetActorLocation().x() << "," << a->GetActorLocation().z() << "\n";
//            mCubes.push_back(new Cube(a->GetActorLocation(), c->mHalfLength*2, QVector3D(1.f, 1.f, 0.f), GL_LINES));
//            mCubes.back()->SetActorLocation(a->GetActorLocation());
//            mCubes.back()->Init();
//        }
//    }

//    for (auto c : mCubes)
//    {
//        c->Draw(mModelLocation);
//    }

//    for (auto c : mCubes)
//    {
//        delete c;
//    }
//    mCubes.clear();

    // Check each object in the world for collision
    for (auto actor : mActors)
    {
        Boundry2D* coll = actor->GetCollisionComponent();
        if (!coll) continue; // Actor has no collision

        std::vector<Actor*> found;
        mQuadtree->Query(found, coll);
        //std::cout << "Collision count for " << actor->name << ": " << found.size() << ".\n";
        if (!found.empty())
        {
            for (auto otherActor : found)
            {
                if (otherActor != actor)
                {
                    actor->OnCollision(otherActor);
                    //std::cout << "Other collision!\n";
                    break;
                }
            }

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
//    for (int i{}; i < mActors.size(); i++)
//    {
//        if (mActors[i] == actor) mActors.erase(mActors.begin() + i);
//    }
    auto it = std::find(mActors.begin(), mActors.end(), actor);
    if (it != mActors.end()) mActors.erase(it);

    mRenderer->Remove(actor);

    // We don't need to remove it from the quadtree as it is updated each tick.
    //mQuadtree->Remove(actor);
}
