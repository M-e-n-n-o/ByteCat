#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec2 texCoord;

out v2f
{
	vec2 uv;
	vec3 cameraPos;
	vec3 worldPos;
} output;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
					
uniform vec3 _CameraPos;

void main()
{		
	output.uv = texCoord;

	// Object space
//	output.cameraPos = (inverse(modelMatrix) * vec4(_CameraPos, 1.0)).xyz;
//	output.worldPos = vertexPos;
	
	// World space
	output.cameraPos = _CameraPos;
	output.worldPos = (modelMatrix * vec4(vertexPos, 1.0)).xyz;
					
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPos, 1.0);
}