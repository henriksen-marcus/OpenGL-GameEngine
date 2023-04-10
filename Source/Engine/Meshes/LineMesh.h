#pragma once
#include "Source/Engine/MeshComponent.h"

class QVector3D;

class LineMesh : public MeshComponent
{
public:
	LineMesh(Actor* parent, const QVector3D& color = QVector3D(1.0f, 1.0f, 1.0f)) :
	MeshComponent(parent, GL_LINES)
	{
		mVertices.emplace_back(0.0f, 0.0f, 0.0f, color);
		mVertices.emplace_back(0.f, 0.0f, 1.f, color);
		mIndices.push_back(0);
		mIndices.push_back(1);
		mDrawMode = GL_LINES;
		Init();
	}
};