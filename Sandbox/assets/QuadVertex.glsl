#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out v2f
{
    vec2 uv;
    vec3 viewVector;
} output;

uniform mat4 _viewMatrix;
uniform mat4 _projectionMatrix;
uniform mat4 _modelMatrix;

void main()
{
    output.uv = aTexCoords;

    vec3 viewVector = (inverse(_projectionMatrix) * vec4(aTexCoords * 2 - 1, 0, -1)).xyz;
    output.viewVector = (inverse(_viewMatrix) * vec4(viewVector, 0)).xyz;

    gl_Position = _modelMatrix * vec4(aPos.xy, 0.0, 1.0);
} 