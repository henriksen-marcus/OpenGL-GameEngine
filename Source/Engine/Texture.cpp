#include "Texture.h"


Texture::Texture() :
  mTextureID(0),
  mLocalBuffer(nullptr),
  mWidth(0),
  mHeight(0),
  mNumChannels(0)
{
}

Texture::~Texture()
{
	if (mTextureID) glDeleteTextures(1, &mTextureID);
	delete [] mLocalBuffer;
}