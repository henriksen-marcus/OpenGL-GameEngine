#pragma once

#include "BaseObject.h"
#include "Texture.h"

class Texture2D : public Texture
{
public:
    Texture2D(const std::string& path);
    virtual ~Texture2D();

    void Bind(unsigned int slot = 0) override;
    void Unbind() override;
};

