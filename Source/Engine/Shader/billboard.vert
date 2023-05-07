#version 410 core

layout(location = 0) in vec4 positionIn;
layout(location = 2) in vec4 textureIN;

uniform mat4 modelViewMatrix;

void main() 
{
   gl_Position = modelViewMatrix * positionIn;
}
