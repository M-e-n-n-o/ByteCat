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
					
uniform vec3 cameraPos;

void main()
{		
	output.uv = texCoord;

	// Object space
//	output.cameraPos = (inverse(modelMatrix) * vec4(cameraPos, 1.0)).xyz;
//	output.worldPos = vertexPos;
	
	// World space
	output.cameraPos = cameraPos;
	output.worldPos = (modelMatrix * vec4(vertexPos, 1.0)).xyz;

//	output.rayOrigin = output.worldPos;
//	float dist1 = distance(output.cameraPos, vec3(0, 0, 0)) + 2;
//	float dist2 = distance(output.worldPos, vec3(0, 0, 0));
//	if (dist1 < dist2)
//	{
//		output.rayOrigin = output.cameraPos;
//	}
					
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPos, 1.0);
}