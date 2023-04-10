#version 410 core

in vec4 color;
out vec4 fragmentColor;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
    FragColor = vec4(result, 1.0);
    // Color given to current fragment (pixel)
    fragmentColor = color;
}
