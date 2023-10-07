#pragma once
#include "Source/Engine/World.h"
#include "Source/Engine/QuadraticBezier.h"
#include "Source/Engine/CubicBezier.h"

class MeshWalker;
class MeshComponent;
class Timer;

class BarycentricScene : public World
{
public:
	BarycentricScene();
	MeshWalker* mWalker;
	void Tick(float deltaTime) override;
};

