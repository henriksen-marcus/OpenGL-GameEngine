#pragma once
#include "Source/Engine/World.h"

class Eksamen2019Scene : public World
{
public:
	Eksamen2019Scene();
	virtual ~Eksamen2019Scene();

	void BeginPlay() override;
	void Tick(float deltaTime) override;
};
