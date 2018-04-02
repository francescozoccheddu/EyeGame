#version 150 core

in vec3 aPosition;
in vec3 aNormal;
uniform mat4 uProjView;
uniform vec3 uLightPos;
out vec3 vColor;

void main()
{
	vec3 s2l = uLightPos - aPosition;
	float lambert = dot(s2l,aNormal);
	vColor = vec3(1.0) * lambert;
	gl_Position = uProjView * vec4(aPosition, 1.0);
}
