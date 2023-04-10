#pragma once

#include "Source/Engine/MeshComponent.h"

class ArrowMesh : public MeshComponent
{
public:
	ArrowMesh(Actor* parent, float length, const QVector3D& direction = QVector3D(0.f, 0.f, -1.f),
	          const QVector3D& color = QVector3D(1.f, 1.f, 1.f))
		: MeshComponent(parent, GL_LINES)
	{
		float headLength = length / 3.5f; // Length along shaft
		float halfLength = length * 0.5f;

		float headZ = -length / 2.f + headLength; // Reverse the sign of headZ

		float headSize = length * 0.2f; // Arrow width
		float halfHeadSize = headSize * 0.5f;

		// Shaft
		mVertices.emplace_back(0.f, 0.f, halfLength, color);
		// Reverse the sign of z-coordinate
		mVertices.emplace_back(0.f, 0.f, -halfLength, color);
		// Reverse the sign of z-coordinate

		// Head, square
		mVertices.emplace_back(halfHeadSize, halfHeadSize, headZ, color);
		mVertices.emplace_back(-halfHeadSize, halfHeadSize, headZ, color);
		mVertices.emplace_back(-halfHeadSize, -halfHeadSize, headZ, color);
		mVertices.emplace_back(halfHeadSize, -halfHeadSize, headZ, color);

		mIndices.clear();

		// Shaft
		mIndices.push_back(0); // Base
		mIndices.push_back(1); // Cross point

		// Head - connect points to cross point
		mIndices.push_back(1);
		mIndices.push_back(2);

		mIndices.push_back(1);
		mIndices.push_back(3);

		mIndices.push_back(1);
		mIndices.push_back(4);

		mIndices.push_back(1);
		mIndices.push_back(5);

		// Head - make square
		mIndices.push_back(2);
		mIndices.push_back(3);

		mIndices.push_back(3);
		mIndices.push_back(4);

		mIndices.push_back(4);
		mIndices.push_back(5);

		mIndices.push_back(5);
		mIndices.push_back(2);

		MeshComponent::Init();
	}
};
