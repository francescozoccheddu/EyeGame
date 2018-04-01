#version 150 core

in vec3 aPosition;
uniform mat4 uProjView;

void main()
{
	gl_Position = uProjView * vec4(aPosition, 1.0);
}
