#include "XYZ.h"


XYZ::XYZ()
{
	// We are not using an IBO here, just declaring points over again.
    mVertices.push_back(Vertex(0.f, 0.f, 0.f, 1.f, 0.f, 0.f));
    mVertices.push_back(Vertex(1.f, 0.f, 0.f, 1.f, 0.f, 0.f));
	
    mVertices.push_back(Vertex(0.f, 0.f, 0.f, 0.f, 1.f, 0.f));
    mVertices.push_back(Vertex(0.f, 1.f, 0.f, 0.f, 1.f, 0.f));
	
    mVertices.push_back(Vertex(0.f, 0.f, 0.f, 0.f, 0.f, 1.f));
    mVertices.push_back(Vertex(0.f, 0.f, 1.f, 0.f, 0.f, 1.f));

	Init();
}

XYZ::~XYZ()
{
}

void XYZ::Init()
{	
    initializeOpenGLFunctions();

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);
	
	// Generate the actual VBO and put index in mVBO
	glGenBuffers(1, &mVBO);
	
	// Bind it so that it will receive the next call for glBufferData
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	
	// Upload the information in mVertices to the VBO on the GPU memory
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);
	
	/* Tell vertex shader how to read the mVBO array. Start at position 0 in the array.
	 * The shader uses ve3 for position which takes 3 values, so we write 3. Type of data
	 * is float so GL_FLOAT. Don't normalize, GL_FALSE. Now, the size of the whole static array.
	 * We don't use any offset so just 0.
	 */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<GLvoid*>(0));
	
	// Activate the shader options pointer above with index 0 (like layout (location = 0)) for the shader.
	glEnableVertexAttribArray(0);
	
	/* NOTE: Here we go to the next index, 1. We are using vec3 for color, so 3. Here in the last argument
	 * we give an offset, because we don't want to process the first 3 which we use for position, just the
	 * last 3 for color. So we tell OpenGL to skip 3 spaces in the array.
	 */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
	
	// And enable it
	glEnableVertexAttribArray(1);

	// Clear bindings to prepare for future memory operations
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void XYZ::Draw()
{
    initializeOpenGLFunctions();

    UseShader("god");

    Shader* activeShader = GetActiveShader();
    activeShader->SendUniforms();
    glUniformMatrix4fv(activeShader->GetModelLocation(), 1, GL_FALSE, mMatrix.constData());

	// Set the VAO as the current render state, which holds info about the VBO
	glBindVertexArray(mVAO);
	// Draw to screen
	glDrawArrays(GL_LINES, 0, mVertices.size());
	// Unbind VAO
	glBindVertexArray(0);
}
