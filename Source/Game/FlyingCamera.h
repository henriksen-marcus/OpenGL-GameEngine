#pragma once

#include "Source/Engine/Pawn.h"

class CameraComponent;

class FlyingCamera : public Pawn
{
public:
	FlyingCamera(const QVector3D& location = QVector3D());

	void ProcessKeyboard(Movement direction) override;
	void ProcessMouseMovement(float xoffset, float yoffset) override;

	CameraComponent* GetCamera() const { return mCamera; }

	void Tick(float deltaTime) override;

private:
	CameraComponent* mCamera;
};

