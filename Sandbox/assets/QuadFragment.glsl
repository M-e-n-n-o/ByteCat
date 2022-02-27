#version 430 core

#define MAX_STEPS 100
#define MAX_DISTANCE 1000
#define MIN_DISTANCE 0.01

out vec4 fragColor;
  
in v2f
{
    vec2 uv;
	vec3 cameraPos;
    vec3 viewVector;
} input;

uniform sampler2D screenTexture;

float dBox(vec3 point, vec3 scale)
{
	return length(max(abs(point) - scale, 0));
}

float getDistance(vec3 point)
{
	return dBox(point + (vec3(3, 0, -5)), vec3(1));
}

float rayMarch(vec3 ro, vec3 rd)
{
	float dO = 0;
	float dS = 0;

	for (int i = 0; i < MAX_STEPS; i++)
	{
		vec3 point = ro + dO * rd;
		dS = getDistance(point);
		dO += dS;

		if (dS < MIN_DISTANCE || dO > MAX_DISTANCE)
		{
			break;
		}
	}

	return dO;
}

void main()
{
	vec3 ro = input.cameraPos;
	vec3 rd = normalize(input.viewVector);

	vec4 col = vec4(vec3(0), 1);

	float distance = rayMarch(ro, rd);
	if (distance < MAX_DISTANCE)
	{
		col.rgb = texture(screenTexture, input.uv).rgb;
	}

	fragColor = col;
}