#version 410 core

// Input variables that change per vertex
layout(location = 0) in vec3 position_IN;
layout(location = 3) in vec3 normal_IN;

// Input variables that are the same for every vertex
uniform mat4 matrixTransform_IN;
uniform mat4 projection_IN;
uniform mat4 view_IN;

out vec3 geoNormal;

void main()											
{
	// Set the position of the individual vertex
	gl_Position = projection_IN * view_IN * matrixTransform_IN * vec4(position_IN, 1.0);

	//geoNormal = mat3(transpose(inverse(matrixTransform_IN))) * normal_IN;
	geoNormal = vec3(matrixTransform_IN * vec4(normal_IN, 1.f));
}