#version 410 core

in vec4 color;
in vec2 v_TexCoord;
out vec4 fragmentColor;

uniform sampler2D texture;

void main() {

    //vec4 texColor = texture(u_Texture, v_Texture);
    // Color given to current fragment (pixel)
    fragmentColor = color;
}									
	
