#version 440 core

layout(location=0) in vec4 position;
layout(location = 1) in vec4 iColour;
layout(location = 2) in vec2 iTexCoord;

out vec4 color;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position=projection*view*model*position;
    color = iColour;
    texCoord = iTexCoord;
}