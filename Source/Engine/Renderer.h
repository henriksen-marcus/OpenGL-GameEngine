#pragma once

#include "BaseObject.h"
#include "Actor.h"
#include <iostream>

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
    Renderer(unsigned amount = 0)
    {
        //initializeOpenGLFunctions();
        mObjects.reserve(amount);
    }

    /**
     * \brief Add an object to the render list.
     * \param object The object to be drawn.
     */
    virtual void Add(const std::string& name, Actor* object)
    {
        mObjects[name] = object;
    }

    virtual void Remove(const std::string& name)
    {
        mObjects.erase(name);
    }

    virtual void Remove(Actor* actor)
    {
//        for (auto it = mObjects.begin(); it != mObjects.end(); ++it) {
//          if (it->second == actor) mObjects.erase(it->first);
//        }
        auto it = std::find_if(mObjects.begin(), mObjects.end(),
            [&](const auto& pair) { return pair.second == actor; });

        if (it != mObjects.end()) {
            mObjects.erase(it->first);
        }
    }

    virtual Actor* Get(const std::string& name)
    {
        return mObjects.at(name); // Can be nullptr
    }

    /* Run this function once at the start of the game. */
    virtual void BeginPlay()
    {
        for (auto it = mObjects.begin(); it != mObjects.end(); ++it)
        {
            it->second->BeginPlay();
        }
    }

    virtual Actor* Find(std::string name)
    {
        auto it = mObjects.find(name);
        if (it != mObjects.end()) {
            return it->second;
        }
        else {
            return nullptr;
        }
    }

    /**
     * \brief Loop through the listed objects and draw them
     * on the screen.
     * \param modelLocation Shader location of the model matrix, so
     * that the objects can transform.
     */
    virtual void DrawObjects(float deltaTime)
    {
        for (auto it = mObjects.begin(); it != mObjects.end(); ++it)
        {
            it->second->Tick(deltaTime);
            it->second->Draw();
        }
    }

    Actor* operator [] (const std::string& name) { return mObjects.at(name); }


protected:
    std::unordered_map<std::string, Actor*> mObjects;
};
