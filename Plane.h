#pragma once

#include "Actor.h"

class Plane : public Actor
{
public:
    Plane(const QVector3D& location, float sizeX, float sizeY, const QVector3D& color = QVector3D(1.f, 1.f, 1.f), GLenum mode = GL_TRIANGLES);

    void Init() override;
    void Draw(GLint mMatrixLocation = -1) override;

private:
    void InitTriangles();
    void InitLines();

    GLenum mMode;
};
