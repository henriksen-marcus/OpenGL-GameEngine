#version 410 core

// Input variables that change per vertex
layout(location = 0) in vec4 position_IN;
layout(location = 1) in vec4 color_IN;
layout(location = 2) in vec2 texCoord_IN;

// Input variables that are the same for every vertex
uniform mat4 matrixTransform_IN;
uniform mat4 projection_IN;
uniform mat4 view_IN;

// Output variables
out vec4 color;
out vec2 TexCoord;

void main()
{
        // Set the position of the individual vertex
        gl_Position = projection_IN *  view_IN * matrixTransform_IN * position_IN;

        // Change the output color of the vertex
        color = color_IN;
        TexCoord = texCoord_IN;
        //v_TexCoord = texture_IN;
}
