#pragma once

#include "MeshComponent.h"

class PlaneMesh : public MeshComponent
{
public:
    PlaneMesh(const QVector3D& location, float sizeX, float sizeY, const QVector3D& color, GLenum mode = GL_TRIANGLES);

protected:
    void InitTriangles();
    void InitLines();

    GLenum mMode;
};
