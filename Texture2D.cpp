#include "Texture2D.h"

#include "Vendor/stb_image.h"

//#define ASSERT(x) if(!(x)) __debugbreak();
//#define GLCall(x) GLClearColor();\
//    x;\
//    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

//static void GLClearError()
//{
//    while(glGetError() != GL_NO_ERROR);
//}

//static void GLCheckError()
//{
//    while (GLenum error = glGetError())
//    {
//        std::cout << "[OpenGL Error] "
//    }
//}

Texture2D::Texture2D(const std::string& path)
    : mRendererID(0),
      mFilepath(path),
      mLocalBuffer(nullptr),
      mWidth(0),
      mHeight(0),
      mBPP(0)
{
    glGenTextures(1, &mRendererID);
    glBindTexture(GL_TEXTURE_2D, mRendererID);

    stbi_set_flip_vertically_on_load(1);
    mLocalBuffer = stbi_load(path.c_str(), &mWidth, &mHeight, &mBPP, 4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mLocalBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (mLocalBuffer)
        stbi_image_free(mLocalBuffer);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &mRendererID);
}

void Texture2D::Bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, mRendererID);
}

void Texture2D::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
