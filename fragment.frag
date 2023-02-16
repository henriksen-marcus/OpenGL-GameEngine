#version 410 core

in vec4 color;   
out vec4 fragmentColor;     

void main() {
	// Color given to current fragment (pixel)
	fragmentColor = color;   
}									
	