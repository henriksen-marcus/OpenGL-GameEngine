#pragma once
#include "Source/Engine/MeshComponent.h"

class TetrahedronMesh : public MeshComponent
{
public:
	TetrahedronMesh(Actor* parent, float size, float height) : MeshComponent(parent)
	{
		float hSize = size * 0.5f;

		// Bottom plane
		mVertices.emplace_back(hSize, 0.f, hSize, QVector3D(1.f, 1.f, 1.f));
		mVertices.emplace_back(-hSize, 0.f, hSize, QVector3D(1.f, 1.f, 1.f));
		mVertices.emplace_back(0.f, 0.f, -hSize, QVector3D(1.f, 1.f, 1.f));

		// Top point
		mVertices.emplace_back(0.f, height, 0.f, QVector3D(1.f, 1.f, 1.f));

		mIndices.push_back(0);
		mIndices.push_back(1);
		mIndices.push_back(2);

		mIndices.push_back(0);
		mIndices.push_back(1);
		mIndices.push_back(3);

		mIndices.push_back(0);
		mIndices.push_back(3);
		mIndices.push_back(2);

		mIndices.push_back(1);
		mIndices.push_back(3);
		mIndices.push_back(2);

		Init();
	}

	virtual ~TetrahedronMesh(){}
};
