#version 450 core

out vec4 fragColor;

in float layer;

void main()
{
	fragColor = vec4(0.2 * layer, 0.5, 0.5, 1);
}