#include "PlaneMesh.h"
#include "Texture2D.h"

PlaneMesh::PlaneMesh(Actor* parent, const QVector3D& location, float sizeX, float sizeY, const QVector3D& color, GLenum mode)
    :MeshComponent(parent, mode)
{
    mVertices.clear();
    sizeX *= 0.5f; // Center the cube on the given origin
    sizeY *= 0.5f;

    mVertices.emplace_back(sizeX, 0.f, sizeY, color.x(), color.y(), color.z(), 1.f, 0.f);
    mVertices.emplace_back(sizeX, 0.f, -sizeY, color.x(), color.y(), color.z(), 1.f, 1.f);
    mVertices.emplace_back(-sizeX, 0.f, -sizeY, color.x(), color.y(), color.z(), 0.f, 1.f);
    mVertices.emplace_back(-sizeX, 0.f, sizeY, color.x(), color.y(), color.z(), 0.f, 0.f);

    mMode = mode;
    if (mMode == GL_TRIANGLES) InitTriangles();
    else InitLines();
}

void PlaneMesh::InitTriangles()
{
    mIndices.push_back(0);
    mIndices.push_back(1);
    mIndices.push_back(2);

    mIndices.push_back(2);
    mIndices.push_back(3);
    mIndices.push_back(0);
}

void PlaneMesh::InitLines()
{
    mIndices.push_back(0);
    mIndices.push_back(1);

    mIndices.push_back(1);
    mIndices.push_back(2);

    mIndices.push_back(2);
    mIndices.push_back(3);

    mIndices.push_back(3);
    mIndices.push_back(0);
}
