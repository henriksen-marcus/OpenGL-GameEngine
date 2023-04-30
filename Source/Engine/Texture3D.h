#pragma once
#include "Texture.h"

class Texture3D : public Texture
{
public:
	Texture3D(const std::vector<std::string>& paths);
	virtual ~Texture3D();

	void Bind(unsigned int slot = 0) override;
	void Unbind() override;

protected:
	/**
	 * \brief Contains path information for each face of the cubemap.
	 * Order: Right, Left, Top, Bottom, Front, Back.
	 */
	std::vector<std::string> mFaces;
};

