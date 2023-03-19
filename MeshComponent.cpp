#include "MeshComponent.h"
#include "Shader.h"
#include "Texture2D.h"


MeshComponent::MeshComponent(Actor* parent, GLenum drawMode)
    : SceneComponent(parent), mDrawMode(drawMode), mTexture(nullptr)
{

}

MeshComponent::~MeshComponent()
{
    delete mTexture;
}

void MeshComponent::SetTexture(Texture2D* texture)
{
    mTexture = texture;
}

void MeshComponent::SetTexture(std::string path)
{
    mTexture = new Texture2D(path);
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

    //if (mTexture)
    //{
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
    //}

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

void MeshComponent::Draw()
{
    if (mVertices.empty()) return;

    if (mTexture != NULL)
    {
        mTexture->Bind();
        UseShader("texture");
    }
    else
    {
        std::cout << "No texture..\n";
        UseShader("plain");
    }

    // Uniforms specific to the shader.
    Shader* activeShader = GetActiveShader();
    activeShader->SendUniforms();

    glUniformMatrix4fv(activeShader->GetModelLocation(), 1, GL_FALSE, mMatrix.constData());

    glBindVertexArray(mVAO);

    // Decide if we should use IBO or not
    if (!mIndices.empty())
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
        glDrawElements(mDrawMode, mIndices.size(), GL_UNSIGNED_INT, nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}
