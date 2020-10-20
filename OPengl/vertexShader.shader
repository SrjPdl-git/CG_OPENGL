#version 440 core

layout(location=0) in vec4 position;

out vec4 color;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position=projection*model*position;
    color = vec4(clamp(position, 0.f, 1.f));
}