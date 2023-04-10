#version 410 core

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

// Input variables that change per vertex
in vec4 geoColor[];
in vec2 geoTexCoord[];
in vec3 geoNormal[];

uniform mat4 matrixTransform_IN;
uniform mat4 projection_IN;
uniform mat4 view_IN;

// Output variables
out vec4 fragColor;
out vec2 fragTexCoord;
out vec3 fragNormal;

void main()											
{
    mat4 model = projection_IN * view_IN * matrixTransform_IN;
	for (int i = 0; i < gl_in.length(); i++) 
    {
        gl_Position = gl_in[i].gl_Position;
        fragColor = vec4(1.f, 1.f, 0.f, 1.f);
        EmitVertex();

        // Remember to multiply the new vertex by the model too
        gl_Position = gl_in[i].gl_Position + model * vec4(geoNormal[i], 0.f);
        fragColor = vec4(1.f, 1.f, 0.f, 1.f);
        EmitVertex();

        EndPrimitive();
    }
}

//	//mat4 model = projection_IN * view_IN * matrixTransform_IN;
//
//	for (int i = 0; i < gl_in.length(); i++) {
//        // Output the original vertex
//        gl_Position = gl_in[i].gl_Position;
//        fragColor = geoColor[i];
//        fragTexCoord = geoTexCoord[i];
//        fragNormal = geoNormal[i];
//        EmitVertex();
//
//        // Output the vertex again, but with a yellow color
//        gl_Position = gl_in[i].gl_Position + vec4(geoNormal[i], 0.0) * 0.1;
//        // Yellow
//        fragColor = vec4(1.0, 1.0, 0.0, 1.0);
//        fragTexCoord = geoTexCoord[i];
//        fragNormal = geoNormal[i];
//        EmitVertex();
//
//        // Connect the two vertices with a line
//        EndPrimitive();
//    }


