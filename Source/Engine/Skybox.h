#pragma once
#include "VisualObject.h"

class MeshComponent;
class Texture3D;

class Skybox : public VisualObject
{
public:
	Skybox(Texture3D* texture);
	virtual ~Skybox();

	void Init();
	void Draw() override;

protected:
	std::string mShaderName = "skybox";
	Texture3D* mTexture;
};

