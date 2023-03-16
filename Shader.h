#pragma once

#include <QOpenGLFunctions_4_1_Core>

class Shader : protected QOpenGLFunctions_4_1_Core
{
public:
	Shader();
	~Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
    GLuint GetTexture();

	void UseShader();
	void ClearShader();

    inline GLuint GetID() { return shaderID; }

    void SendUniforms();

private:
    GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformTexture;

    static constexpr float defaultFOV{75.f};
    static constexpr float aspectRatio{16.f/9.f};
    static constexpr float nearPlane{0.01f};
    static constexpr float farPlane{1000.f};

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};


