#version 330 core

out vec4 FragColor;
uniform float mColorR;
uniform float mColorG;
uniform float mColorB;
//uniform float mColorA;

void main()
{
    FragColor = vec4(mColorR, mColorG, mColorB, 1.0);
} 