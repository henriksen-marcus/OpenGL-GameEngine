#version 410 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;

// Input variables that change per vertex
in vec4 geoColor[];
in vec2 geoTexCoord[];
in vec3 geoNormal[];

//uniform mat4 matrixTransform_IN;
//uniform mat4 projection_IN;
//uniform mat4 view_IN;

//uniform vec3 lightPosition;
//uniform vec3 lightColor;
//uniform bool useLighting;

// Output variables
out vec4 fragColor;
out vec2 fragTexCoord;
out vec3 fragNormal;

void main()											
{
	//mat4 model = projection_IN * view_IN * matrixTransform_IN;

	for (int i = 0; i < gl_in.length(); i++) {
        // Output the original vertex
        gl_Position = gl_in[i].gl_Position;
        fragColor = geoColor[i];
        fragTexCoord = geoTexCoord[i];
        fragNormal = geoNormal[i];
        EmitVertex();

        // Output the vertex again, but with a yellow color
        gl_Position = gl_in[i].gl_Position + vec4(geoNormal[i], 0.0) * 0.1;
        // Yellow
        fragColor = vec4(1.0, 1.0, 0.0, 1.0);
        fragTexCoord = geoTexCoord[i];
        fragNormal = geoNormal[i];
        EmitVertex();

        // Connect the two vertices with a line
        EndPrimitive();
    }
}