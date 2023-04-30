#include "Bezier.h"

Bezier::Bezier(const QVector3D& start) :
MeshComponent(nullptr, GL_LINES), mResolution(5), mColor(1, 1, 1), mStart(start)
{
}

Bezier::~Bezier()
{
}


void Bezier::InitPoints()
{
    if (mVertices_points.empty()) return;

	initializeOpenGLFunctions();

    glGenVertexArrays(1, &mVAO_points);
    glBindVertexArray(mVAO_points);

    glGenBuffers(1, &mVBO_points);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO_points);
    glBufferData(GL_ARRAY_BUFFER, mVertices_points.size() * sizeof(Vertex), mVertices_points.data(), GL_STATIC_DRAW);

    // [x,y,z,r,g,b,u,v,a,m,c]
    // Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<GLvoid*>(0));
    glEnableVertexAttribArray(0);

    // Colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Normals
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind
    glBindVertexArray(0); // This should be above the unbind beneath
}

void Bezier::Draw()
{
	MeshComponent::Draw();

	if (!bDrawPoints) return;
	if (mVertices_points.empty()) return;

	UseShader(mShaderName);

    // Uniforms specific to the shader.
    Shader* activeShader = GetActiveShader();
    activeShader->SendUniforms();

    glUniformMatrix4fv(activeShader->GetModelLocation(), 1, GL_FALSE, mMatrix.constData());

    glBindVertexArray(mVAO_points);
	glPointSize(10.f);
    glDrawArrays(GL_POINTS, 0, mVertices_points.size());
    glBindVertexArray(0);
}
