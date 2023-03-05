﻿#pragma once


#include "BaseObject.h"
#include "Actor.h"

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

    virtual Actor* Get(const std::string& name)
    {
        return mObjects.at(name); // Can be nullptr
    }

    /* Run this function once at the start of the game. */
    virtual void BeginPlay(GLint modelLocation)
    {
        for (auto it = mObjects.begin(); it != mObjects.end(); ++it)
        {
            it->second->BeginPlay();
            it->second->Draw(modelLocation);
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
    virtual void DrawObjects(GLint modelLocation, float deltaTime)
    {
        for (auto it = mObjects.begin(); it != mObjects.end(); ++it)
        {
            it->second->Tick(deltaTime);
            it->second->Draw(modelLocation);
        }
    }

    Actor* operator [] (const std::string& name) { return mObjects.at(name); }


protected:
    std::unordered_map<std::string, Actor*> mObjects;
};
