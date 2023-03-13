#include "PlaneMesh.h"
#include "Texture2D.h"

PlaneMesh::PlaneMesh(const QVector3D& location, float sizeX, float sizeY, const QVector3D& color, GLenum mode)
{
    mVertices.clear();
    sizeX *= 0.5f; // Center the cube on the given origin
    sizeY *= 0.5f;

    mTexture = new Texture2D("Textures/tex.png");

    mVertices.emplace_back(sizeX, 0.f, sizeY, color.x(), color.y(), color.z(), 1.f, 0.f);
    mVertices.emplace_back(sizeX, 0.f, -sizeY, color.x(), color.y(), color.z(), 1.f, 1.f);
    mVertices.emplace_back(-sizeX, 0.f, -sizeY, color.x(), color.y(), color.z(), 0.f, 1.f);
    mVertices.emplace_back(-sizeX, 0.f, sizeY, color.x(), color.y(), color.z(), 0.f, 0.f);

    mMode = mode;
    if (mMode == GL_TRIANGLES) InitTriangles();
    else InitLines();

    MeshComponent::Init();
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

void PlaneMesh::Draw(GLint mMatrixLocation)
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

    UseShader("texture");

    mTexture->Bind();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glDrawElements(mMode, mIndices.size(), GL_UNSIGNED_INT, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    mTexture->Unbind();

    glBindVertexArray(0);
}
