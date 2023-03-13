#pragma once

#include "MeshComponent.h"

class PlaneMesh : public MeshComponent
{
public:
    PlaneMesh(const QVector3D& location, float sizeX, float sizeY, const QVector3D& color, GLenum mode);

    void Draw(GLint mModelLocation = -1);

protected:
    void InitTriangles();
    void InitLines();

    GLenum mMode;
};

