#pragma once
#include "Source/Engine/World.h"
#include "Source/Engine/ZigZag.h"
#include "Source/Engine/Billboard.h"

class CubemapScene : public World
{
public:
	CubemapScene();
	virtual ~CubemapScene();

	void BeginPlay() override;
	void Tick(float deltaTime) override;

	Actor* mesh;
	Actor* plane;
	Actor* bActor;

	Billboard* billboard;

	ZigZag<float> myZigZag{0.0f, 5.0f, 0.01f};
	ZigZag<int> intZig{0, 21, 1};
};
