#pragma once
#include "Source/Engine/MeshComponent.h"

class Billboard : public MeshComponent
{
public:
	Billboard(Actor* parent, float sizeX, float sizeY, const QVector3D& color = QVector3D(1.f, 1.f, 1.f));
	virtual ~Billboard();

	void Tick(float deltaTime) override;
};

