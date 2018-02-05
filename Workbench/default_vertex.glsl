#version 150 core

in vec3 aPosition;
in vec3 aColor;
uniform mat4 uProjView;
out vec3 vColor;

void main()
{
	vColor = aColor + 0.8;
	gl_Position = uProjView * vec4(aPosition, 1.0);
}
