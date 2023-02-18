#version 330 core
in vec2 PassTexCoord;
		
out vec4 FragColor;

uniform sampler2D tex;

void main()
{
	vec4 col = texture(tex, PassTexCoord);
	
	if (col.a < 0.1)
	{
		discard;
	}

	FragColor = col;
}