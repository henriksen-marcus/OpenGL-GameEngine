#include "Texture3D.h"
#include "Vendor/stb_image.h"

Texture3D::Texture3D(const std::vector<std::string>& paths)
	: Texture()
{
	initializeOpenGLFunctions();
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureID);

	for (int i = 0; i < paths.size(); i++)
	{
		mLocalBuffer = stbi_load(paths[i].c_str(), &mWidth, &mHeight, &mNumChannels, 0);
		if (mLocalBuffer)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mLocalBuffer);
		}
		else 
		{
			std::cout << "TEXTURE3D::Failed to load image at index " + std::to_string(i) + ".\n";
			return;
		}
		stbi_image_free(mLocalBuffer);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Texture3D::~Texture3D()
{
}

void Texture3D::Bind(unsigned slot)
{
	initializeOpenGLFunctions();
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureID);
}

void Texture3D::Unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
