#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec3 aNormal;

out vec3 TexCoords;

uniform mat4 _modelMatrix;
uniform mat4 _viewMatrix;
uniform mat4 _projectionMatrix;

void main()
{
    TexCoords = aPos;
    gl_Position = _projectionMatrix * _viewMatrix * _modelMatrix * vec4(aPos, 1.0);
} 