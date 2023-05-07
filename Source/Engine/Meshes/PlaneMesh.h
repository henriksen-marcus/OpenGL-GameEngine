#pragma once

#include "Source/Engine/MeshComponent.h"

class PlaneMesh : public MeshComponent
{
public:
    PlaneMesh(Actor* parent, float sizeX, float sizeY, const QVector3D& color = QVector3D(1.f, 1.f, 1.f), GLenum mode = GL_TRIANGLES);

protected:
    void InitTriangles();
    void InitLines();
};

