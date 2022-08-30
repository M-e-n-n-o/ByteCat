#version 300 es

layout (location = 0) in vec3 VertexPos;
layout (location = 1) in vec2 TexCoord;

out vec2 PassTexCoord;
	
uniform mat4 _modelMatrix;
uniform mat4 _projectionMatrix;

void main()
{
	PassTexCoord = TexCoord;
	gl_Position = _projectionMatrix * _modelMatrix * vec4(VertexPos, 1.0);
}