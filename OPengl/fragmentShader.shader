#version 440 core
layout(location=0) out vec4 colour;

in vec4 color;
in vec2 texCoord;
uniform sampler2D texture0;

void main()
{
   colour = texture(texture0, texCoord);
}