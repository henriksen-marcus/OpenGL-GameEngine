#pragma once
#include "Source/Engine/World.h"
#include "Source/Engine/CubicBezier.h"
#include "Source/Engine/ZigZag.h"

class CurveScene : public World
{
public:
	CurveScene();
	virtual ~CurveScene();

	void BeginPlay() override;
	void Tick(float deltaTime) override;

	CubicBezier bez = CubicBezier(QVector3D());
	ZigZag<float> zig = ZigZag(0.f, 1.f, 0.005f);
	Actor* curveCube;
};
