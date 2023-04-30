#pragma once
#include "BaseObject.h"

class Texture : public BaseObject
{
public:
	Texture();
	virtual ~Texture();

	virtual void Bind(unsigned int slot = 0) = 0;
	virtual void Unbind() = 0;

	inline int GetWidth() const { return mWidth; }
	inline int GetHeight() const { return mHeight; }

protected:
	/* ID assigned by OpenGL for this texture. */
	GLuint mTextureID{};

	/* Raw image data. */
	unsigned char* mLocalBuffer;

    std::string mFilepath;
	int mWidth{}, mHeight{}, mNumChannels{};
};

