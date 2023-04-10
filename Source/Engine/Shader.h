#pragma once

#include <QOpenGLFunctions_4_1_Core>

class Shader : protected QOpenGLFunctions_4_1_Core
{
public:
	Shader();
	~Shader() override;

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();

	void UseShader();
	void ClearShader();

    inline GLuint GetID() const { return shaderID; }

    void SendUniforms();

	void SetVec3(const std::string& name, const QVector3D& value);
	void SetBool(const std::string& name, bool value);
	void SetInt(const std::string& name, int value);
	void SetFloat(const std::string& name, float value);
	void SetMat4(const std::string& name, const QMatrix4x4& value);

protected:
    GLuint shaderID, uniformProjection, uniformModel, uniformView;

    static constexpr float defaultFOV{75.f};
    static constexpr float aspectRatio{16.f/9.f};
    static constexpr float nearPlane{0.01f};
    static constexpr float farPlane{1000.f};

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};


