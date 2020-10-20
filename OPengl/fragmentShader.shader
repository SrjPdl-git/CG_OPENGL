#version 440 core
layout(location=0) out vec4 colour;

in vec4 color;
uniform vec4 uColour;

void main()
{
   colour = color;
}