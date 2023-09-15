#pragma once
#include "Source/Engine/World.h"


class MeshWalker;
class MeshComponent;
class Timer;
class TriangleSurface;
class HealthPack;
class Enemy;
class LightSwitch;

class Eksamen2023Scene : public World
{
public:
	Eksamen2023Scene();
	virtual ~Eksamen2023Scene();

	MeshComponent* GetSurface() const { return mSurface; }
	void AddScore();

	Actor* mSurfaceActor;
	MeshComponent* mSurface;
	Actor* texturePlane;
	MeshWalker* mWalker;
	HealthPack* trophy;
	Enemy* enemy;
	LightSwitch* lightSwitch;


	int playerScore{ 0 };

	void BeginPlay() override;
	void Tick(float deltaTime) override;
	void RestartGame() override;
};

