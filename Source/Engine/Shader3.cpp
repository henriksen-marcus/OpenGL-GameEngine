#include "Shader3.h"

void Shader3::CreateFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string geometryString = ReadFile(geometryLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* geometryCode = geometryString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	CompileShader(vertexCode, geometryCode, fragmentCode);
}

void Shader3::CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode)
{
	initializeOpenGLFunctions();

	shaderID = glCreateProgram();
	if (!shaderID)
	{
		qDebug() << "Error creating shader program!";
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, geometryCode, GL_GEOMETRY_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result{};
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderID);

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shaderID, "matrixTransform_IN");
	uniformProjection = glGetUniformLocation(shaderID, "projection_IN");
    uniformView = glGetUniformLocation(shaderID, "view_IN");
    //uniformTexture = glGetUniformLocation(shaderID, "texture_IN");
}
