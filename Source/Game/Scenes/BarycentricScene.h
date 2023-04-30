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
	MeshComponent* GetSurface() const { return mSurface; }
	MeshComponent* mSurface;
	MeshWalker* mWalker;
	void Tick(float deltaTime) override;

	Actor* temp;
	MeshComponent* m;
	MeshComponent* d;

	int ticks = 0;
	Timer* timer;


	float myt = 0;
	bool dir = false;

	CubicBezier bez = CubicBezier(QVector3D());
};

