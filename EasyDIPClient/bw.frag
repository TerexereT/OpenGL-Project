#version 330 core

out vec4 FragColor;

uniform vec3 mColorA;
uniform vec3 mColorL;

//uniform float mColorA;

void main()
{
    FragColor = vec4(mColorA, 1.0);
} 