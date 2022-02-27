#version 330 core

in vec2 passTexCoord;

out vec4 fragColor;

uniform sampler2D tex;

void main()
{
	vec4 tex = texture(tex, vec2(passTexCoord));
	fragColor = tex + vec4(0, 0.3, 0, 0);
}