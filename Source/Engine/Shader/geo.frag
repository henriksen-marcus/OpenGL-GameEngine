#version 410 core

in vec4 fragColor;

out vec4 fragmentColor;

void main()
{
	fragmentColor = fragColor;
}