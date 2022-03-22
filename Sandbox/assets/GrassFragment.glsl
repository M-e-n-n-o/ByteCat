#version 450 core

out vec4 fragColor;

in g2f
{
	vec2 uv;
	float layer;
} i;

uniform sampler2D tex;

void main()
{
	fragColor = texture(tex, i.uv);
	//fragColor = vec4(0.2 * i.layer, 0.5, 0.5, 1);
}