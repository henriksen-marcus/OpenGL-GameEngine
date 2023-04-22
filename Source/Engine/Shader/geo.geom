#version 410 core

layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

// Input variables that change per vertex
in vec3 geoNormal[];

uniform mat4 matrixTransform_IN;
uniform mat4 projection_IN;
uniform mat4 view_IN;

// Output variables
out vec4 fragColor;

void main()											
{
    mat4 model = projection_IN * view_IN * matrixTransform_IN;
	for (int i = 0; i < gl_in.length(); i++) 
    {
        gl_Position = gl_in[i].gl_Position;
        fragColor = vec4(0.f, 1.f, 1.f, 1.f); // Yellow
        EmitVertex();

        // Remember to multiply the new vertex by the model too
        gl_Position = gl_in[i].gl_Position + projection_IN * view_IN * vec4(geoNormal[i], 0.f);
        fragColor = vec4(0.f, 1.f, 1.f, 1.f); // Yellow
        EmitVertex();

        EndPrimitive();
    }
}




