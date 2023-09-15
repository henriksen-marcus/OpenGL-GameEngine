#pragma once
#include "Source/Engine/Pawn.h"

class SpringArmComponent;
class CameraComponent;
class LightCube;
class TriangleSurface;
class LineActor;
class Timer;

class MeshWalker : public Pawn
{
public:
	MeshWalker(const QVector3D& location = QVector3D());
	void BeginPlay() override;
	void Tick(float deltaTime) override;
	void Draw() override;
	void SetAsCurrent() override;
	void ProcessKeyboard(Movement direction) override;
	void OnPickup(PickupType pickup) override;

	/* Switch between first and third person camera. */
	void SwitchCamera();

	void OnGameReset();

	MeshComponent* mSurface;
	MeshComponent* testcube;
	Timer* switchTimer;
	Timer* lightTimer;
	SpringArmComponent* mSpringArm;

protected:
	CameraComponent* mThirdPersonCamera;
	CameraComponent* mFirstPersonCamera;
	LightCube* mLightCube;
	LineActor* mLine;
};

