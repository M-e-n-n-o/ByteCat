#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec3 aNormal;

out VS_OUT
{
	vec3 pos;
    vec3 normal;
    vec2 uv;
    vec4 fragPosLightSpace;
} vs_out;

uniform mat4 _modelMatrix;
uniform mat4 _viewMatrix;
uniform mat4 _projectionMatrix;

uniform mat4 _lightSpaceMatrix;

void main()
{
    vs_out.pos = vec3(_modelMatrix * vec4(aPos, 1.0));
    vs_out.normal = transpose(inverse(mat3(_modelMatrix))) * aNormal;
    vs_out.uv = aUv;
    vs_out.fragPosLightSpace = _lightSpaceMatrix * vec4(vs_out.pos, 1.0);
    gl_Position = _projectionMatrix * _viewMatrix * vec4(vs_out.pos, 1.0);
}