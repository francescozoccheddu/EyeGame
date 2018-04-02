#version 150 core

out vec4 outColor;
in vec3 vColor;

void main()
{
    outColor = vec4(vColor,1.0);
}