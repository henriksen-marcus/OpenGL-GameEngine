#include "MeshComponent.h"
#include "Texture2D.h"


MeshComponent::MeshComponent()
{

}

void MeshComponent::SetTexture(Texture2D* texture)
{
    mTexture = texture;
}

void MeshComponent::Init()
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

void MeshComponent::Draw(GLint mModelLocation)
{
    if (mVertices.empty()) return;

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

    if (mTexture) mTexture->Bind();

    // Decide if we should use IBO or not
    if (!mIndices.empty())
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
        glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

    if (mTexture) mTexture->Unbind();
    glBindVertexArray(0);
}
