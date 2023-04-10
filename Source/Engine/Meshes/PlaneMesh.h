#pragma once

#include "Source/Engine/MeshComponent.h"

class PlaneMesh : public MeshComponent
{
public:
    PlaneMesh(Actor* parent, const QVector3D& location, float sizeX, float sizeY, const QVector3D& color, GLenum mode = GL_TRIANGLES);

protected:
    void InitTriangles();
    void InitLines();
};

