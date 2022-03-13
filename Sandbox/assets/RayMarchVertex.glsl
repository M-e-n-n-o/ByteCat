#version 450 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec2 texCoord;

out v2f
{
	vec2 uv;
	vec3 originPos;
	vec3 hitPos;
} o;

uniform mat4 _modelMatrix;
uniform mat4 _viewMatrix;
uniform mat4 _projectionMatrix;
					
uniform vec3 _cameraPos;

void main()
{		
	o.uv = texCoord;

	// Object space
//	o.originPos = (inverse(_modelMatrix) * vec4(_cameraPos, 1.0)).xyz;
//	o.hitPos = vertexPos;

	// World space
	o.originPos = _cameraPos;
	o.hitPos = (_modelMatrix * vec4(vertexPos, 1.0)).xyz;
					
	gl_Position = _projectionMatrix * _viewMatrix * _modelMatrix * vec4(vertexPos, 1.0);
}