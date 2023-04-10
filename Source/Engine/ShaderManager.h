#pragma once

#include "BaseObject.h"
#include "Shader.h"

class ShaderManager : public BaseObject
{
public:
    static ShaderManager& GetInstance()
    {
        static ShaderManager instance;
        return instance;
    }

    std::unordered_map<std::string, Shader*> Shaders;
    Shader* ActiveShader;

private:
    ShaderManager(){};
    ~ShaderManager(){};

    ShaderManager(const ShaderManager&) = delete;
    ShaderManager& operator = (const ShaderManager&) = delete;
};

