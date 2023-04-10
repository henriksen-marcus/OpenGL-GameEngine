#version 410 core

// Input variables that change per vertex
layout(location = 0) in vec3 position_IN;
layout(location = 1) in vec4 color_IN;
layout(location = 2) in vec2 texCoord_IN;
layout(location = 3) in vec3 normal_IN;

// Input variables that are the same for every vertex
uniform mat4 matrixTransform_IN;
uniform mat4 projection_IN;
uniform mat4 view_IN;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform bool useLighting;

// Output variables
out vec4 geoColor;
out vec2 geoTexCoord;
out vec3 geoNormal;

void main()											
{
	// Set the position of the individual vertex
	gl_Position = projection_IN * view_IN * matrixTransform_IN * vec4(position_IN, 1.0);
	
	// Pass the texture coordinates to the fragment shader
	geoTexCoord = texCoord_IN;

	// Change the output color of the vertex
	geoColor = color_IN;

	geoNormal = mat3(transpose(inverse(matrixTransform_IN))) * normal_IN;
}