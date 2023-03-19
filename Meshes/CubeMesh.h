#pragma once

#include "MeshComponent.h"

class CubeMesh : public MeshComponent
{
public:
    CubeMesh(Actor* parent, float size, const QVector3D& color = QVector3D(1.f, 1.f, 1.f), GLenum drawMode = GL_TRIANGLES) :
    MeshComponent(parent, drawMode)
    {
        size *= 0.5f; // Center the cube on the given origin

//        mVertices.emplace_back(-size, -size, -size, color); // Origin 0
//        mVertices.emplace_back(size, -size, -size, color); // X 1
//        mVertices.emplace_back(-size, size, -size, color); // Y 2
//        mVertices.emplace_back(-size, -size, size, color); // Z 3

//        mVertices.emplace_back(size, -size, size, color); // XZ 4
//        mVertices.emplace_back(size, size, -size, color); // XY 5

//        mVertices.emplace_back(-size, size, size, color); // ZY 6
//        mVertices.emplace_back(size, size, size, color); // XYZ 7

        mVertices.emplace_back(-size, -size, -size, color, 1.0f, 1.0f); // Origin 0
        mVertices.emplace_back(size, -size, -size, color, 1.0f, 1.0f); // X 1
        mVertices.emplace_back(-size, size, -size, color, 0.0f, 0.0f); // Y 2
        mVertices.emplace_back(-size, -size, size, color, 0.0f, 0.0f); // Z 3

        mVertices.emplace_back(size, -size, size, color, 1.0f, 0.0f); // XZ 4
        mVertices.emplace_back(size, size, -size, color, 1.0f, 1.0f); // XY 5

        mVertices.emplace_back(-size, size, size, color, 0.0f, 0.0f); // ZY 6
        mVertices.emplace_back(size, size, size, color, 1.0f, 0.0f); // XYZ 7

        if (mDrawMode == GL_LINES) InitLines();
        else InitTriangles();
        Init();
    }

protected:
    void InitTriangles()
    {
        mIndices.clear();

        // Origin side
        mIndices.push_back(0);
        mIndices.push_back(1);
        mIndices.push_back(2);

        mIndices.push_back(1);
        mIndices.push_back(2);
        mIndices.push_back(5);

        mIndices.push_back(0);
        mIndices.push_back(3);
        mIndices.push_back(2);

        mIndices.push_back(2);
        mIndices.push_back(3);
        mIndices.push_back(6);
        // Bottom
        mIndices.push_back(0);
        mIndices.push_back(1);
        mIndices.push_back(3);

        mIndices.push_back(1);
        mIndices.push_back(3);
        mIndices.push_back(4);

        // Opposite origin
        mIndices.push_back(2);
        mIndices.push_back(5);
        mIndices.push_back(6);

        mIndices.push_back(5);
        mIndices.push_back(6);
        mIndices.push_back(7);

        mIndices.push_back(3);
        mIndices.push_back(4);
        mIndices.push_back(6);

        mIndices.push_back(4);
        mIndices.push_back(6);
        mIndices.push_back(7);

        mIndices.push_back(1);
        mIndices.push_back(4);
        mIndices.push_back(5);

        mIndices.push_back(4);
        mIndices.push_back(5);
        mIndices.push_back(7);
    }

    void InitLines()
    {
        mIndices.clear();

        mIndices.push_back(0);
        mIndices.push_back(1);

        mIndices.push_back(0);
        mIndices.push_back(2);

        mIndices.push_back(0);
        mIndices.push_back(3);

        mIndices.push_back(1);
        mIndices.push_back(5);

        mIndices.push_back(5);
        mIndices.push_back(2);

        mIndices.push_back(3);
        mIndices.push_back(6);

        mIndices.push_back(6);
        mIndices.push_back(2);

        mIndices.push_back(1);
        mIndices.push_back(4);

        mIndices.push_back(4);
        mIndices.push_back(3);

        mIndices.push_back(6);
        mIndices.push_back(7);

        mIndices.push_back(7);
        mIndices.push_back(5);

        mIndices.push_back(4);
        mIndices.push_back(7);
    }
};
