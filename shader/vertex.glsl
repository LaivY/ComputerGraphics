#version 330 core
in vec3 vPos;
in vec3 vColor;

out vec3 pColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	pColor = vColor;
	gl_Position = proj * view * model * vec4(vPos, 1.0);
}