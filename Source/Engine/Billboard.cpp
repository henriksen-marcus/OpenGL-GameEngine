#include "Billboard.h"
#include "Texture2D.h"

Billboard::Billboard(Actor* parent, float sizeX, float sizeY, const QVector3D& color)
	: MeshComponent(parent, GL_TRIANGLES)
{
	mVertices.emplace_back(sizeX, 0.f, sizeY, color, 1.f, 0.f, 0.f, 1.f, 0.f);
    mVertices.emplace_back(sizeX, 0.f, -sizeY, color, 1.f, 1.f, 0.f, 1.f, 0.f);
    mVertices.emplace_back(-sizeX, 0.f, -sizeY, color, 0.f, 1.f, 0.f, 1.f, 0.f);
    mVertices.emplace_back(-sizeX, 0.f, sizeY, color, 0.f, 0.f, 0.f, 1.f, 0.f);

    mIndices.push_back(0);
    mIndices.push_back(1);
    mIndices.push_back(2);

    mIndices.push_back(2);
    mIndices.push_back(3);
    mIndices.push_back(0);

    Init();
}

Billboard::~Billboard()
{
}

void Billboard::Tick(float deltaTime)
{
	
}

//void Billboard::Init()
//{
//	if (mIBO != 0)
//    {
//        glDeleteVertexArrays(1, &mVAO);
//    	glDeleteBuffers(1, &mIBO);
//		mIBO = 0;
//	}
//
//    if (mVertices.empty()) return;
//
//    initializeOpenGLFunctions();
//
//    glGenVertexArrays(1, &mVAO);
//    glBindVertexArray(mVAO);
//
//    glGenBuffers(1, &mVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
//    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);
//
//    // [x,y,z,r,g,b,u,v,a,m,c]
//    // Positions
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<GLvoid*>(0));
//    glEnableVertexAttribArray(0);
//
//    if (mTexture != nullptr)
//    {
//        // Texture coordinates
//        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
//        glEnableVertexAttribArray(2);
//    }
//
//    if (!mIndices.empty())
//    {
//        glGenBuffers(1, &mIBO);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);
//    }
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind
//    glBindVertexArray(0); // This should be above the unbind beneath
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind
//}
//
//void Billboard::Draw()
//{
//	if (mVertices.empty()) return;
//
//    if (mTexture) mTexture->Bind();
//
//	UseShader("billboard");
//
//    // Uniforms specific to the shader.
//    Shader* activeShader = GetActiveShader();
//
//    glUniformMatrix4fv(0, 1, GL_FALSE, viewmodelmatrix.constData());
//
//    glBindVertexArray(mVAO);
//
//    // Decide if we should use IBO or not
//    if (!mIndices.empty())
//    {
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
//        glDrawElements(mDrawMode, mIndices.size(), GL_UNSIGNED_INT, nullptr);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//    }
//    else glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
//
//    glBindVertexArray(0);
//    if (mTexture) mTexture->Unbind();
//}
