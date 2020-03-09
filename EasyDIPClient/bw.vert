#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 proj;
uniform mat4 modl;
uniform mat4 view;

void main()
{
	FragPos = vec3(modl * vec4(aPos, 1.0));
	Normal = aNormal;

	gl_Position = proj * view * vec4(FragPos,1.0);
}