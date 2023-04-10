#pragma once

#include "BaseObject.h"

class Texture2D : public BaseObject
{
public:
    Texture2D(const std::string& path);
    ~Texture2D();

    void Bind(unsigned int slot = 0);
    void Unbind();

    inline int GetWidth() const { return mWidth; }
    inline int GetHeight() const { return mHeight; }

protected:
    GLuint mRendererID;
    std::string mFilepath;
    unsigned char* mLocalBuffer;
    int mWidth, mHeight, mBPP;
};

