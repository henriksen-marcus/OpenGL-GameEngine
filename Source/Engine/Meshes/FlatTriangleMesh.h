#pragma once

#include "Source/Engine/MeshComponent.h"

class FlatTriangleMesh : public MeshComponent
{
public:
	FlatTriangleMesh(Actor* parent)
		: MeshComponent(parent, GL_TRIANGLES)
	{
		mVertices.emplace_back(0, 0, -0.5f, 1.f, 0.f, 0.f);
		mVertices.emplace_back(-0.5f, 0, 0.5f, 0.f, 1.f, 1.f);
		mVertices.emplace_back(0.5f, 0, 0.5f, 0.f, 1.f, 1.f);
		mIndices.clear();
		mIndices.push_back(0);
		mIndices.push_back(1);
		mIndices.push_back(2);
		GenerateNormals();
		MeshComponent::Init();
	}
};
