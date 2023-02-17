#pragma once

#include "Actor.h"

class Cube : public Actor
{
public:
    Cube(const QVector3D& origin, float size, const QVector3D& color, GLenum drawMode = GL_TRIANGLES, bool init = false);
    
    void Init() override;

    void Draw(GLint modelLocation = -1) override;

protected:
    void InitTriangles();
    void InitLines();
    
    GLenum mode = GL_TRIANGLES;
};
