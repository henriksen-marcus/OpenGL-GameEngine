#version 410 core

in vec4 color;
in vec2 TexCoord;

uniform sampler2D ourTexture;

out vec4 fragmentColor;

void main() {

    //vec4 texColor = texture(u_Texture, v_Texture);
    // Color given to current fragment (pixel)
    fragmentColor = texture(ourTexture, TexCoord);
}

