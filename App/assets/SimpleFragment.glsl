#version 300 es

in vec2 PassTexCoord;
		
out vec4 FragColor;

uniform sampler2D tex;
uniform bool useTex;
	
uniform vec4 color;

void main()
{
	vec4 col = color;

	col *= mix(col, texture(tex, PassTexCoord), useTex);
	
	FragColor = col;
}