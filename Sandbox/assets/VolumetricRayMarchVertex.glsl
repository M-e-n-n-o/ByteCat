#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec2 texCoord;

out v2f
{
	vec2 uv;
	vec3 cameraPos;
	vec3 worldPos;
} output;

uniform mat4 _modelMatrix;
uniform mat4 _viewMatrix;
uniform mat4 _projectionMatrix;
					
uniform vec3 _cameraPos;

void main()
{		
	output.uv = texCoord;

	// Object space
	output.cameraPos = (inverse(_modelMatrix) * vec4(_cameraPos, 1.0)).xyz;
	output.worldPos = vertexPos;
	
	// World space
//	output.cameraPos = _cameraPos;
//	output.worldPos = (_modelMatrix * vec4(vertexPos, 1.0)).xyz;
					
	gl_Position = _projectionMatrix * _viewMatrix * _modelMatrix * vec4(vertexPos, 1.0);
}