#pragma once
#include "Source/Engine/MeshComponent.h"

class SphereMesh : public MeshComponent
{
public:
	SphereMesh(Actor* parent, float radius, const QVector3D& color = QVector3D(1.f, 1.f, 1.f))
		: MeshComponent(parent, GL_TRIANGLES)
	{
		for (int x = 0; x <= 20; ++x)
		{
			for (int y = 0; y <= 20; ++y)
			{
				float xSegment = (float)x / 20.f;
				float ySegment = (float)y / 20.f;
				float xPos = radius * std::cos(xSegment * 2.f * M_PI) * std::sin(ySegment * M_PI);
				float yPos = radius * std::cos(ySegment * M_PI);
				float zPos = radius * std::sin(xSegment * 2.f * M_PI) * std::sin(ySegment * M_PI);
				mVertices.emplace_back(xPos, yPos, zPos, color);
			}
		}

		for (int x = 0; x < 20; ++x)
		{
			for (int y = 0; y < 20; ++y)
			{
				int first = (x * (20 + 1)) + y;
				int second = first + 1;
				int third = ((x + 1) * (20 + 1)) + y;
				int fourth = third + 1;

				mIndices.push_back(first);
				mIndices.push_back(third);
				mIndices.push_back(second);

				mIndices.push_back(second);
				mIndices.push_back(third);
				mIndices.push_back(fourth);
			}

		}

		Init();
	}
};

