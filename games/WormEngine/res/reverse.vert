#version 330 core

in vec4 vert;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vert * vec4(-1.0, 1.0, 1.0, 1.0);
}
