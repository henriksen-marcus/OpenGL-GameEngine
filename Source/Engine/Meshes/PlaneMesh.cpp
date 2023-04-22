#include "PlaneMesh.h"
#include "Source/Engine/Texture2D.h"

PlaneMesh::PlaneMesh(Actor* parent, const QVector3D& location, float sizeX, float sizeY, const QVector3D& color, GLenum mode)
    :MeshComponent(parent, mode)
{
    mVertices.clear();
    mColor = color;
    sizeX *= 0.5f; // Center the cube on the given origin
    sizeY *= 0.5f;

    SetWorldLocation(location);

    mVertices.emplace_back(sizeX, 0.f, sizeY, color, 1.f, 0.f, 0.f, 1.f, 0.f);
    mVertices.emplace_back(sizeX, 0.f, -sizeY, color, 1.f, 1.f, 0.f, 1.f, 0.f);
    mVertices.emplace_back(-sizeX, 0.f, -sizeY, color, 0.f, 1.f, 0.f, 1.f, 0.f);
    mVertices.emplace_back(-sizeX, 0.f, sizeY, color, 0.f, 0.f, 0.f, 1.f, 0.f);

    bUseLighting = false;

    if (mDrawMode == GL_TRIANGLES) 
    {
    	InitTriangles();
		GenerateNormals();
    }
    else InitLines();
    Init();

    UseShader("geo");
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
