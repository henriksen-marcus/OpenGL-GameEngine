#pragma once
#include "Source/Engine/MeshComponent.h"

class TetrahedronMesh : public MeshComponent
{
public:
	TetrahedronMesh(Actor* parent, float size, float height, const QVector3D& color = QVector3D(1.f, 1.f, 1.f)) : MeshComponent(parent)
	{
		float hSize = size * 0.5f;

		// Bottom plane
		mVertices.emplace_back(hSize, 0.f, hSize, color);
		mVertices.emplace_back(-hSize, 0.f, hSize, color);
		mVertices.emplace_back(0.f, 0.f, -hSize, color);

		// Top point
		mVertices.emplace_back(0.f, height, 0.f, color);

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
