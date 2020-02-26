#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 proj;
uniform mat4 modl;
uniform mat4 view;

void main()
{
	gl_Position = proj * view * modl * vec4(aPos,1.0);
}