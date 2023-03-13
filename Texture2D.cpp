#include "Texture2D.h"
#include "Vendor/stb_image.h"
#include <iostream>

Texture2D::Texture2D(const std::string& path)
    : mRendererID(0),
      mFilepath(path),
      mLocalBuffer(nullptr),
      mWidth(0),
      mHeight(0),
      mBPP(0)
{
    // Load actual image from disk
    stbi_set_flip_vertically_on_load(1);
    mLocalBuffer = stbi_load(path.c_str(), &mWidth, &mHeight, &mBPP, 4);

    if (mLocalBuffer)
    {
        glGenTextures(1, &mRendererID);
        glBindTexture(GL_TEXTURE_2D, mRendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mLocalBuffer);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

           stbi_image_free(mLocalBuffer);
    }
    else
    {
        std::cout << "Failed to load image.\n";
    }
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &mRendererID);
}

void Texture2D::Bind(unsigned int slot)
{
    initializeOpenGLFunctions();
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, mRendererID);
}

void Texture2D::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
