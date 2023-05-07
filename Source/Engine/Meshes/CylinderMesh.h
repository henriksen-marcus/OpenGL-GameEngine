#pragma once
#include "Source/Engine/MeshComponent.h"

class CylinderMesh : public MeshComponent
{
public:
	CylinderMesh(Actor* parent, float height, float radius, unsigned resolution) : MeshComponent(parent)
	{
		float halfHeight = height * 0.5f;

		for (int i = 0; i < resolution; i++)
		{
			float angle = 2.f * M_PI * (float)i / (float)resolution;
			float x = std::cos(angle) * radius;
			float z = std::sin(angle) * radius;

			// Bottom
			mVertices.emplace_back(x, -halfHeight, z, QVector3D(1.f, 1.f, 1.f));
			// Top
			mVertices.emplace_back(x, halfHeight, z, QVector3D(1.f, 1.f, 1.f));
		}

		// Middle points for caps
		mVertices.emplace_back(0.f, -halfHeight, 0.f, QVector3D(1.f, 1.f, 1.f));
		int bottomMiddle = mVertices.size() - 1;
		mVertices.emplace_back(0.f, halfHeight, 0.f, QVector3D(1.f, 1.f, 1.f));
		int topMiddle = mVertices.size() - 1;

		for (int i = 0; i < resolution; i++)
		{
			int bottom = i * 2;
			int top = bottom + 1;
			int nextBottom = (bottom + 2) % (resolution * 2);
			int nextTop = (top + 2) % (resolution * 2);

			mIndices.push_back(bottom);
			mIndices.push_back(top);
			mIndices.push_back(nextBottom);

			mIndices.push_back(nextBottom);
			mIndices.push_back(top);
			mIndices.push_back(nextTop);

			// Caps, triangle fan
			mIndices.push_back(bottom);
			mIndices.push_back(bottomMiddle);
			mIndices.push_back(nextBottom);

			mIndices.push_back(top);
			mIndices.push_back(topMiddle);
			mIndices.push_back(nextTop);
		}

		Init();
	}

	virtual ~CylinderMesh(){}
};
