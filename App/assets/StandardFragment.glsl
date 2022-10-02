#version 450 core

in vec2 uv;

out vec4 fragColor;

uniform sampler2D tex;

void main()
{
	vec3 texColor = texture(tex, uv).rgb;

	fragColor = vec4(texColor, 1);
}