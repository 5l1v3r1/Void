#version 330 core

uniform vec4 color;
uniform sampler2D image;
out vec4 finalColor;

void main()
{
    finalColor = color;
}
