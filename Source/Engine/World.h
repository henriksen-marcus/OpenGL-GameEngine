#pragma once

#include "BaseObject.h"
#include "Renderer.h"

class Actor;
class QElapsedTimer;
class PauseableTimer;
class Quadtree;
class Cube;
class Renderer;

class World : public BaseObject
{
public:
    World();
    ~World();

    /* Runs tick and draw on all actors in the world. */
    virtual void Tick(float deltaTime);

    bool ContainsActor(Actor* actor);
    bool ContainsActor(const std::string& name);

    bool IsPaused() { return isPaused; }
    void Pause(bool shouldPause);
    std::string GetMapName() { return mapName; }
    float GetDeltaSeconds() { return mDeltaTime; }
    float GetTimeSeconds();
    float GetUnpausedTimeSeconds();

    template<class T>
    inline Actor* SpawnActor(const std::string& name, const QVector3D& location = QVector3D());

    template<class T>
    inline Actor* SpawnActor(const std::string& name, MeshComponent* mesh);

    void RemoveActor(Actor* actor);

    void BeginPlay() { mRenderer->BeginPlay(); };

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
inline Actor* World::SpawnActor(const std::string& name, const QVector3D& location)
{
    static_assert(is_derived_from<T, Actor>::value, "SpawnActor failed: T must be derived from Actor.");
    static_assert(std::is_default_constructible<T>::value, "SpawnActor failed: T must be default constructible.");
    
    T* newActor = new T();
    if (newActor)
    {
        newActor->SetActorLocation(location);
        //newActor->SetActorRotation(rotation);

        mActors.push_back(newActor);
        mRenderer->Add(name, newActor);
    }
    return newActor;
}

template <class T>
Actor* World::SpawnActor(const std::string& name, MeshComponent* mesh)
{
    static_assert(is_derived_from<T, Actor>::value, "SpawnActor failed: T must be derived from Actor.");
	static_assert(std::is_default_constructible<T>::value, "SpawnActor failed: T must be default constructible.");

    T* newActor = new T();
    if (newActor)
    {
        mesh->SetupAttachment(newActor);
        newActor->SetMesh(mesh);
        mActors.push_back(newActor);
        mRenderer->Add(name, newActor);
    }
    return newActor;
}


