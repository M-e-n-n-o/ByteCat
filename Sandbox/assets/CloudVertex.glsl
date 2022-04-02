#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out v2f
{
    vec2 uv;
    vec3 cameraPos;
    vec3 viewVector;
} o;

uniform vec3 _cameraPos;
uniform mat4 _viewMatrix;
uniform mat4 _projectionMatrix;
uniform mat4 _modelMatrix;

void main()
{
    o.uv = aTexCoords;

    vec3 viewVector = (inverse(_projectionMatrix) * vec4(aTexCoords * 2 - 1, 0, 1)).xyz;
    o.viewVector = (inverse(_viewMatrix) * vec4(viewVector, 0)).xyz;

    o.cameraPos = (inverse(_viewMatrix) * vec4(_cameraPos, 1)).xyz;

    gl_Position = vec4(aPos, 0.0, 1.0);
} 