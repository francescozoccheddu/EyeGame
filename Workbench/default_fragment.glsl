#version 130 core

out vec4 outColor;
in vec3 vLight;
in vec3 vNormal;

void main()
{
    vec3 diffuse = vec3(1.0);
    float lambert = dot(vLight, vNormal);
    outColor = vec4(diffuse * lambert, 1.0);
}