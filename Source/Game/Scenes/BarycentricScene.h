#pragma once
#include "Source/Engine/World.h"

class MeshWalker;
class MeshComponent;
class Timer;

class BarycentricScene : public World
{
public:
	BarycentricScene();
	MeshComponent* GetSurface() const { return mSurface; }
	MeshComponent* mSurface;
	MeshWalker* mWalker;
	void Tick(float deltaTime) override;

	int ticks = 0;
	Timer* timer;
};

