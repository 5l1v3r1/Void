#version 330 core

uniform vec4 color;
uniform sampler2D image;
in vec2 fragTextureCoord;
out vec4 finalColor;

void main()
{
    finalColor = color;
    finalColor = texture(image, fragTextureCoord);
}
