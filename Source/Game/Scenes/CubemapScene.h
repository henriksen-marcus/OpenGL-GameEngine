#pragma once
#include "Source/Engine/World.h"

class CubemapScene : public World
{
public:
	CubemapScene();
	virtual ~CubemapScene();

	void BeginPlay() override;
	void Tick(float deltaTime) override;
};
