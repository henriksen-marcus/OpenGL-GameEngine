#pragma once
#include "BaseObject.h"

class Actor;
class Skybox;

struct RenderObject
{
    Actor* obj;
    std::string name = "";
};

class Renderer : public BaseObject
{
public:
    /**
     * \param amount The amount of objects you expect to render.
     */
    Renderer(unsigned amount = 0);

    /**
     * \brief Add an object to the render list.
     * \param object The object to be drawn.
     */
    virtual void Add(const std::string& name, Actor* object);

    virtual void Remove(const std::string& name);

    virtual void Remove(Actor* actor);

    virtual Actor* Get(const std::string& name);

    virtual void SetSkybox(Skybox* skybox) { mSkybox = skybox; }

    /* Run this function once at the start of the game. */
    virtual void BeginPlay();

    virtual Actor* Find(const std::string& name);

    /**
     * \brief Loop through the listed objects and draw them
     * on the screen.
     * \param modelLocation Shader location of the model matrix, so
     * that the objects can transform.
     */
    virtual void DrawObjects(float deltaTime);

    Actor* operator [] (const std::string& name) { return mObjects.at(name); }


protected:
    std::unordered_map<std::string, Actor*> mObjects;
    Skybox* mSkybox = nullptr;
};
