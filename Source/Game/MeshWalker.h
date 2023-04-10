#pragma once
#include "Source/Engine/Pawn.h"

class SpringArmComponent;
class CameraComponent;
class LightCube;
class TriangleSurface;

class MeshWalker : public Pawn
{
public:
	MeshWalker(const QVector3D& location = QVector3D());
	void BeginPlay() override;
	void Tick(float deltaTime) override;
	void Draw() override;
	void SetAsCurrent() override;
	void ProcessKeyboard(Movement direction) override;
	MeshComponent* mSurface;
protected:
	SpringArmComponent* mSpringArm;
	CameraComponent* mCamera;
	LightCube* mLightCube;
};

