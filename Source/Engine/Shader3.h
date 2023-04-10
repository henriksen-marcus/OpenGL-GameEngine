#pragma once

#include "Source/Engine/Shader.h"

class Shader3 : public Shader
{
public:
	void CreateFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation);
	void CompileShader(const char* vertexCode, const char* geometryLocation, const char* fragmentCode);
};

