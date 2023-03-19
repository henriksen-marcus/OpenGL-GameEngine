#version 410 core

in vec4 color;
in vec2 TexCoord;

uniform sampler2D tex1;
uniform sampler2D tex2;

out vec4 fragmentColor;

void main() {

    // Color given to current fragment (pixel)
    fragmentColor = texture(tex1, TexCoord) * color;
}

