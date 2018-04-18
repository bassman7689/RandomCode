#version 150
in vec2 TexCoord;

out vec4 finalColor;

uniform sampler2D tex;

void main()
{
    finalColor = texture(tex, TexCoord);
}
