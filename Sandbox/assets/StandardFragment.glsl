#version 330 core

in vec2 passTexCoord;

out vec4 fragColor;

uniform sampler3D tex;

uniform float _Time;

void main()
{
	float z = mod(_Time / 200, 512);
	fragColor = texture(tex, vec3(passTexCoord, z));
}