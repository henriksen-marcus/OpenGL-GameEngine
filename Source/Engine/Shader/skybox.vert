#version 410 core

layout (location = 0) in vec3 position_IN;

uniform mat4 projection_IN;
uniform mat4 view_IN;

out vec3 fragTexCoords;

void main()
{
    // Remove translation from the view matrix
    gl_Position = projection_IN * mat4(mat3(view_IN)) * vec4(position_IN, 1.0);
    fragTexCoords = position_IN;
}  
