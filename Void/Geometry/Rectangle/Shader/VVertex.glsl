#version 330 core

uniform mat4 projection;
in vec3 position;
in vec2 textureCoord;

void main()
{
    gl_Position = projection * vec4(position, 1.0);
}
