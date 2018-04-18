#version 330 core

in vec4 vert;
in vec2 texcoord;

out vec2 TexCoord;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vert;
    TexCoord = texcoord;
}
