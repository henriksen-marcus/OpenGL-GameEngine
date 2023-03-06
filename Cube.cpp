#include "Cube.h"

#include <iostream>


Cube::Cube(const QVector3D& origin, float size, const QVector3D& color, GLenum drawMode, bool init)
{
    mVertices.clear();

    size *= 0.5f; // Center the cube on the given origin

    mVertices.emplace_back(-size, -size, -size, color.x(), color.y(), color.z()); // Origin 0
    mVertices.emplace_back(size, -size, -size, color.x(), color.y(), color.z()); // X 1
    mVertices.emplace_back(-size, size, -size, color.x(), color.y(), color.z()); // Y 2
    mVertices.emplace_back(-size, -size, size, color.x(), color.y(), color.z()); // Z 3

    mVertices.emplace_back(size, -size, size, color.x(), color.y(), color.z()); // XZ 4
    mVertices.emplace_back(size, size, -size, color.x(), color.y(), color.z()); // XY 5

    mVertices.emplace_back(-size, size, size, color.x(), color.y(), color.z()); // ZY 6
    mVertices.emplace_back(size, size, size, color.x(), color.y(), color.z()); // XYZ 7

    size *= 2;

    mLocation = origin;
    UpdateModelMatrix();
    mode = drawMode;

    if (init) Init();
}

void Cube::Init()
{
    if (mVertices.empty())
    {
        printf("Empty mVertices!");
        return;
    }

    if (mode == GL_LINES) InitLines();
    else InitTriangles();

    initializeOpenGLFunctions();

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);
    // [x,y,z,r,g,b,u,v]
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<GLvoid*>(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind
    glBindVertexArray(0); // This should be above the unbind beneath
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind
}

void Cube::Draw(GLint mModelLocation)
{
    initializeOpenGLFunctions();

    glBindVertexArray(mVAO);

    // Draw with no transformations we we have not gotten the shader "model" location.
    if (mModelLocation != -1)
    {
        QMatrix4x4 temp;
        glUniformMatrix4fv(mModelLocation, 1, GL_FALSE, mMatrix.constData());
    }
    else
    {
        QMatrix4x4 temp;
        glUniformMatrix4fv(1, 1, GL_FALSE, temp.constData());
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glDrawElements(mode, mIndices.size(), GL_UNSIGNED_INT, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Cube::InitTriangles()
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

void Cube::InitLines()
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
