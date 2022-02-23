#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec2 texCoord;

out v2f
{
	vec2 uv;
	vec3 originPos;
	vec3 hitPos;
} output;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
					
uniform vec3 cameraPos;

void main()
{		
	output.uv = texCoord;

	// Use object space
	output.originPos = (inverse(modelMatrix) * vec4(cameraPos, 1.0)).xyz;
	output.hitPos = vertexPos;
					
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPos, 1.0);
}