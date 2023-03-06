#pragma once

#include "BaseObject.h"
#include "Renderer.h"

class Actor;
class QElapsedTimer;
class PauseableTimer;
class Quadtree;
class Cube;

class World : public BaseObject
{
public:
    World();

    void InitWorld();

    /* Runs tick and draw on all actors in the world. */
    virtual void Tick(float deltaTime, GLint mModelLocation);

    bool ContainsActor(Actor* actor);
    bool ContainsActor(const std::string& name);

    bool IsPaused() { return isPaused; }
    void Pause(bool shouldPause);
    std::string GetMapName() { return mapName; }
    float GetDeltaSeconds() { return mDeltaTime; }
    float GetTimeSeconds();
    float GetUnpausedTimeSeconds();

    template<class T>
    inline Actor* SpawnActor(const QVector3D& location, const QQuaternion& rotation);
    void RemoveActor(Actor* actor);

    Renderer* mRenderer;

protected:
    Quadtree* mQuadtree;
    std::vector<Actor*> mActors;
    std::string mapName;

    bool isPaused;
    bool isWorldInitialized{};

    float mDeltaTime{};
    float timeSeconds{};
    float unpausedTimeSeconds{};

    PauseableTimer* worldTimer;
    QElapsedTimer* worldUnpausedTimer;
};

template<class T>
inline Actor* World::SpawnActor(const QVector3D& location, const QQuaternion& rotation)
{
    //if (std::is_base_of<Actor, T>::value);
    static_assert(std::is_base_of<Actor, T>::value, "T must be derived from Actor");

    T* newActor = new T();
    if (newActor)
    {
        newActor->SetActorLocation(location);
        newActor->SetActorRotation(rotation);

        mActors.push_back(newActor);
        mRenderer->Add(newActor);
    }
    return newActor;
}

