#version 440 core

out vec4 colour;

in vec3 normal;
in vec2 texCoord;

uniform sampler2D texture0;

struct DirectionalLight
{
	vec3 colour;
	vec3 direction;
	float ambientStrength;
	float diffuseStrength;

};

uniform DirectionalLight directionalLight;

void main()
{
	vec4 ambient = vec4(directionalLight.colour, 1.f) * directionalLight.ambientStrength;

	vec4 diffuse = vec4(directionalLight.colour, 1.f)
				   * directionalLight.diffuseStrength
				   * max(dot(normalize(normal),normalize(directionalLight.direction)),0);

	colour = texture(texture0, texCoord) * (ambient + diffuse);
}