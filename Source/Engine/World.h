#pragma once

#include "BaseObject.h"
#include "Renderer.h"

class Actor;
class QElapsedTimer;
class PauseableTimer;
class Quadtree;
class Cube;
class Renderer;
class MeshComponent;

class World : public BaseObject
{
public:
    World();
    virtual ~World();

    /* Runs tick and draw on all actors in the world. */
    virtual void Tick(float deltaTime);

    bool ContainsActor(Actor* actor);
    bool ContainsActor(const std::string& name);

    bool IsPaused() { return isPaused; }
    void Pause(bool shouldPause);
    std::string GetMapName() { return mapName; }
    float GetDeltaSeconds() { return mDeltaTime; }

    /**
     * \return Seconds since the world was created.
     */
    float GetTimeSeconds();

    /**
     * \return Seconds since the world was created,
     * including the time the game was paused.
     */
    float GetUnpausedTimeSeconds();

    /**
     * \brief Sets the glClearColor value for this world.
     */
    void SetWorldColor(const QVector3D& color) { mWorldColor = color; }
    QVector3D GetWorldColor() const { return mWorldColor; }

    /**
     * \brief Spawn an actor into the world. Automatically constructs
     * an actor and adds it to the render queue.
     * \tparam T The class derived from actor to construct.
     * \param name The name of the actor in the render queue.
     * \param location Spawn location.
     * \return Pointer to the spawned actor.
     */
    template<class T>
    inline T* SpawnActor(const std::string& name, const QVector3D& location = QVector3D());

    /**
     * \brief Spawn an actor into the world based on a mesh.
     * Automatically constructs an actor and adds it to the render queue.
     * \tparam T The class derived from actor to construct.
     * \param name The name of the actor in the render queue.
     * \param mesh The pre-constructed meshcomponent.
     * \return Pointer to the spawned actor.
     */
    template<class T>
    inline T* SpawnActor(const std::string& name, MeshComponent* mesh);

    /**
     * \brief Removes an actor from the render queue
     * as well as any other lists like the collision tree.
     * \param actor The actor to remove.
     */
    void RemoveActor(Actor* actor);

    virtual void BeginPlay();;

    Renderer* mRenderer;

protected:
    // Collision detection
    Quadtree* mQuadtree;

    std::vector<Actor*> mActors;

    std::string mapName;

    bool isPaused{};
    bool isWorldInitialized{};

    float mDeltaTime{};
    float timeSeconds{};
    float unpausedTimeSeconds{};

    PauseableTimer* worldTimer;
    QElapsedTimer* worldUnpausedTimer;

    QVector3D mWorldColor{};
};

template<class T>
inline T* World::SpawnActor(const std::string& name, const QVector3D& location)
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
T* World::SpawnActor(const std::string& name, MeshComponent* mesh)
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


