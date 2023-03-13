#include "Plane.h"

#include "Texture2D.h"

Plane::Plane(const QVector3D& location, float sizeX, float sizeY, const QVector3D& color, GLenum mode)
{
    mVertices.clear();
    sizeX *= 0.5f; // Center the cube on the given origin
    sizeY *= 0.5f;

    //Texture2D tex("Textures/tex.png");
    //tex.Bind();

    mVertices.emplace_back(sizeX, 0.f, sizeY, color.x(), color.y(), color.z(), 1.f, 0.f);
    mVertices.emplace_back(sizeX, 0.f, -sizeY, color.x(), color.y(), color.z(), 1.f, 1.f);
    mVertices.emplace_back(-sizeX, 0.f, -sizeY, color.x(), color.y(), color.z(), 0.f, 1.f);
    mVertices.emplace_back(-sizeX, 0.f, sizeY, color.x(), color.y(), color.z(), 0.f, 0.f);

    SetActorLocation(location);

    mMode = mode;
    if (mMode == GL_TRIANGLES) InitTriangles();
    else InitLines();

    Init();
}

void Plane::Init()
{
    if (mVertices.empty()) return;

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

//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);

    if (!mIndices.empty())
    {
        glGenBuffers(1, &mIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind
    glBindVertexArray(0); // This should be above the unbind beneath
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind
}

void Plane::Draw(GLint mMatrixLocation)
{
    glBindVertexArray(mVAO);

    // Draw with no transformations we we have not gotten the shader "model" location.
    if (mMatrixLocation != -1)
    {
        QMatrix4x4 temp;
        glUniformMatrix4fv(mMatrixLocation, 1, GL_FALSE, mMatrix.constData());
    }
    else
    {
        QMatrix4x4 temp;
        glUniformMatrix4fv(1, 1, GL_FALSE, temp.constData());
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glDrawElements(mMode, mIndices.size(), GL_UNSIGNED_INT, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Plane::InitTriangles()
{
    mIndices.push_back(0);
    mIndices.push_back(1);
    mIndices.push_back(2);

    mIndices.push_back(2);
    mIndices.push_back(3);
    mIndices.push_back(0);
}

void Plane::InitLines()
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

