#pragma once
#include "CubeMesh.h"

class LightCube : public CubeMesh
{
public:
	LightCube(Actor* parent, float size, const QVector3D& color = QVector3D(1.f, 1.f, 1.f), GLenum drawMode = GL_TRIANGLES)
		: CubeMesh(parent, size, color, drawMode)
	{
		mColor = color;
	}

	void Draw() override
	{
		if (mVertices.empty()) return;

		UseShader("god");

	    // Uniforms specific to the shader.
	    Shader* activeShader = GetActiveShader();
	    activeShader->SendUniforms();

		if (activateLight)
		{
			activeShader->SetVec3("lightColor", mColor);
		}
		else
		{
			activeShader->SetVec3("lightColor", {});
		}
		

		activeShader->SetVec3("lightPosition", mWorldLocation);

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

	bool activateLight = true;
};