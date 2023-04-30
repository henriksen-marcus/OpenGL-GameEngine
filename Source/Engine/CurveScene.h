#pragma once
#include "Source/Engine/World.h"

class CurveScene : public World
{
public:
	CurveScene();
	virtual ~CurveScene();

	void BeginPlay() override;
	void Tick(float deltaTime) override;
};

