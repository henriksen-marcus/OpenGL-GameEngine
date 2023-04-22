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

// Output variables
out vec4 fragColor;
out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragPosition;

void main()											
{
	// Set the position of the individual vertex
	gl_Position = projection_IN * view_IN * matrixTransform_IN * vec4(position_IN, 1.f);
	
	// Pass the texture coordinates to the fragment shader
	fragTexCoord = texCoord_IN;

	// Change the output color of the vertex
	fragColor = color_IN;

	//fragNormal = mat3(transpose(inverse(matrixTransform_IN))) * normal_IN;
	//fragNormal = normal_IN;
	fragNormal = mat3(transpose(inverse(matrixTransform_IN))) * normal_IN;
	fragPosition = vec3(matrixTransform_IN * vec4(position_IN, 1.f));
}