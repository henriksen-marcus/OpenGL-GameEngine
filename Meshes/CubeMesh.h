#pragma once

#include "MeshComponent.h"

class CubeMesh : public MeshComponent
{
public:
    CubeMesh(Actor* parent, float size, const QVector3D& color = QVector3D(1.f, 1.f, 1.f), GLenum drawMode = GL_TRIANGLES) :
    MeshComponent(parent, drawMode)
    {
        size *= 0.5f; // Center the cube on the given origin

        mVertices.emplace_back(-size, -size, -size, color);  
        mVertices.emplace_back(size, -size, -size, color);
        mVertices.emplace_back(-size, size, -size, color);
        mVertices.emplace_back(-size, -size, size, color);  

        mVertices.emplace_back(size, -size, size, color);  
        mVertices.emplace_back(size, size, -size, color);

        mVertices.emplace_back(-size, size, size, color); 
        mVertices.emplace_back(size, size, size, color); 

        //mVertices.emplace_back(-size, -size, -size, color, 1.0f, 1.0f); // Origin 0
        //mVertices.emplace_back(size, -size, -size, color, 1.0f, 1.0f); // X 1
        //mVertices.emplace_back(-size, size, -size, color, 0.0f, 0.0f); // Y 2
        //mVertices.emplace_back(-size, -size, size, color, 0.0f, 0.0f); // Z 3

        //mVertices.emplace_back(size, -size, size, color, 1.0f, 0.0f); // XZ 4
        //mVertices.emplace_back(size, size, -size, color, 1.0f, 1.0f); // XY 5

        //mVertices.emplace_back(-size, size, size, color, 0.0f, 0.0f); // ZY 6
        //mVertices.emplace_back(size, size, size, color, 1.0f, 0.0f); // XYZ 7

        if (mDrawMode == GL_LINES) InitLines();
        else InitTriangles();
        Init();
    }

    //float d = 0.f;
    //QQuaternion q;

    //void Tick(float deltaTime) override
    //{
	   // d+=0.2f;
    //    SetFollowParent(false);
    //    auto e = q * QQuaternion::fromEulerAngles(QVector3D(0.f, 0.f, d));
    //    mMatrix.setToIdentity();
    //    //mMatrix.rotate(d, QVector3D(0.f, 0.f, 1.f));
    //    //mMatrix.rotate(QQuaternion::fromEulerAngles(e));
    //    mMatrix.rotate(e);
    //}

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
