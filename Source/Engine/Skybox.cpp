#include "Skybox.h"
#include "Source/Engine/Meshes/CubeMesh.h"
#include "Texture3D.h"

Skybox::Skybox(Texture3D* texture) :
	mTexture(texture)
{
	for (int x = -1; x <= 1; x += 2)
	{
		for (int y = -1; y <= 1; y += 2)
		{
			for (int z = -1; z <= 1; z += 2)
			{
				mVertices.emplace_back(QVector3D(x, y, z));
			}
		}
	}

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

	Init();
}


Skybox::~Skybox()
{
}

void Skybox::Init()
{
	initializeOpenGLFunctions();

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), mIndices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Skybox::Draw()
{
	initializeOpenGLFunctions();
	glDepthMask(GL_FALSE);
	//glDisable(GL_CULL_FACE);


	if (mVertices.empty()) return;
    if (mTexture) mTexture->Bind();

	UseShader(mShaderName);

    // Uniforms specific to the shader.
    Shader* activeShader = GetActiveShader();
	activeShader->SendUniforms();
    glUniformMatrix4fv(activeShader->GetModelLocation(), 1, GL_FALSE, mMatrix.constData());

    glBindVertexArray(mVAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    if (mTexture) mTexture->Unbind();


	//glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
}
