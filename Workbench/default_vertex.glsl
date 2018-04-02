#version 130 core

in vec3 aPosition;
in vec3 aNormal;
uniform mat4 uProjView;
uniform vec3 uLightPos;
out vec3 vLight;
out vec3 vNormal;

void main()
{
	vNormal = aNormal;
	vLight = uLightPos - aPosition;
	gl_Position = uProjView * vec4(aPosition, 1.0);
}
