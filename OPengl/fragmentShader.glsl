#version 440 core
out vec4 colour;

in vec4 color;
in vec2 texCoord;

uniform sampler2D texture0;

struct DirectionalLight
{
	vec3 lightColour;
	float ambientStrength;

};

uniform DirectionalLight directionalLight;

void main()
{
	vec3 ambient=directionalLight.lightColour*directionalLight.ambientStrength;
   colour = vec4(ambient,1.f)*texture(texture0, texCoord);
}