#pragma once
#include "Source/Engine/MeshComponent.h"

class TestMesh : public MeshComponent
{
public:
	TestMesh(Actor* parent, float size) : MeshComponent(parent)
	{
		float sizeX = size;
		float sizeY = size;
		auto color = QVector3D(1.f, 1.f, 1.f);
		mVertices.emplace_back(sizeX, -5.f, sizeY, color, 1.f, 0.f, 0.f, 1.f, 0.f);
	    mVertices.emplace_back(sizeX, 1.f, -sizeY, color, 1.f, 1.f, 0.f, 1.f, 0.f);
	    mVertices.emplace_back(-sizeX, 0.f, -sizeY, color, 0.f, 1.f, 0.f, 1.f, 0.f);
	    mVertices.emplace_back(-sizeX, 0.f, sizeY, color, 0.f, 0.f, 0.f, 1.f, 0.f);
		mIndices = {
			0, 1, 2,
			2, 3, 0
		};
		GenerateNormals();
		Init();
	}
};

