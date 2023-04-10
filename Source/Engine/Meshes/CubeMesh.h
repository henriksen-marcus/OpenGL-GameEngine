#pragma once

#include "Source/Engine/MeshComponent.h"

class CubeMesh : public MeshComponent
{
public:
    CubeMesh(Actor* parent, float size, const QVector3D& color = QVector3D(1.f, 1.f, 1.f), GLenum drawMode = GL_TRIANGLES) :
    MeshComponent(parent, drawMode)
    {
        mColor = color;
        size *= 0.5f; // Center the cube on the given origin

        for (int x = -1; x <= 1; x += 2)
        {
	        for (int y = -1; y <= 1; y += 2)
	        {
		        for (int z = -1; z <= 1; z += 2)
		        {
			        mVertices.emplace_back(QVector3D(x, y, z) * size, color);
		        }
	        }
        }

        if (mDrawMode == GL_LINES) InitLines();
        else 
        {
        	InitTriangles();
            GenerateNormals();
        }
        Init();
    }

protected:
    void InitTriangles()
    {
        mIndices = {
	        0, 1, 3,
	        3, 2, 0,
	        1, 5, 7,
	        7, 3, 1,
	        5, 4, 6,
	        6, 7, 5,
	        4, 0, 2,
	        2, 6, 4,
	        2, 3, 7,
	        7, 6, 2,
	        4, 5, 1,
	        1, 0, 4
        };
    }

    void InitLines()
    {
	    mIndices = {
		    0, 1,
		    1, 3,
		    3, 2,
		    2, 0,
		    1, 5,
		    5, 7,
		    7, 3,
		    3, 1,
		    5, 4,
		    4, 6,
		    6, 7,
		    7, 5,
		    4, 0,
		    0, 2,
		    2, 6,
		    6, 4,
		    2, 3,
		    3, 7,
		    7, 6,
		    6, 2,
		    4, 5,
		    5, 1,
		    1, 0,
		    0, 4
	    };
    }
};
