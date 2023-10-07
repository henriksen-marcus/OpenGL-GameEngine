#pragma once
#include "Source/Engine/World.h"

class LightCube;

class PresentationWorld : public World
{
public:
	PresentationWorld();
	void BeginPlay() override;
	void Tick(float deltaTime) override;

private:
	Actor* mMesh;
	Actor* mLight;
	LightCube* mLightCube;
};

