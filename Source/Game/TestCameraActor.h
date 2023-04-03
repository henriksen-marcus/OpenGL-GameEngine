#pragma once

#include "Source/Engine/Pawn.h"

class CameraComponent;
class MeshComponent;
class SpringArmComponent;
class TestCameraActor : public Pawn
{
public:
	TestCameraActor();
	MeshComponent* camVis;
	SpringArmComponent* springArm;
	CameraComponent* camera;

	void Draw() override;
	void Tick(float deltaTime) override;
};

