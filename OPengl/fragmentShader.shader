#version 440 core
layout(location=0) out vec4 colour;

in vec4 color;

void main()
{
   colour = color;
}