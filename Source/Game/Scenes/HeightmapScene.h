#pragma once
#include "Source/Engine/World.h"

class TriangleSurface;
class FlyingCamera;
class Plane;
class Pawn;

class HeightmapScene : public World
{
public:
	HeightmapScene();

	MeshComponent* mSurface;
	FlyingCamera* fCam;
	Plane *plane;
	Actor* reflectcube;
	Actor* tri;
	Pawn* light;

	MeshComponent* GetSurface() const { return mSurface; }

	void Tick(float deltaTime) override;
};

