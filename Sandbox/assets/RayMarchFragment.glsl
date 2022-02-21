#version 330 core

#define MAX_STEPS 100
#define MIN_DISTANCE 0.001
#define MAX_DISTANCE 100
			
in v2f
{
	vec2 uv;
	vec3 originPos;
	vec3 hitPos;	
} input;

out vec4 FragColor;

uniform sampler2D noiseTexture;


float getDistance(vec3 point)
{
	//float distance = length(point) - 0.5;
	float distance = length(vec2(length(point.xz) - 0.5, point.y)) - 0.1;				

	return distance;
}

			
float rayMarch(vec3 rayOrigin, vec3 rayDirection)
{
	float distanceOrigin = 0;
	float distanceSurface = 0;

	for (int i = 0; i < MAX_STEPS; i++)
	{
		vec3 point = rayOrigin + distanceOrigin * rayDirection;
		distanceSurface = getDistance(point);
		distanceOrigin += distanceSurface;

		if (distanceSurface < MIN_DISTANCE || distanceOrigin > MAX_DISTANCE)
		{
			break;
		}
	}

	return distanceOrigin;
}

vec3 getNormal(vec3 point)
{
	vec2 epsilon = vec2(0.01, 0);
			
	vec3 normal = getDistance(point) - vec3(
		getDistance(point - epsilon.xyy),
		getDistance(point - epsilon.yxy),
		getDistance(point - epsilon.yyx)
		);

	return normalize(normal);
}

float rand(vec2 n)
{ 
	return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

vec3 createCircle(vec3 pos, float diameter, float smoothness)
{
	vec3 col = vec3(length(pos) - 0.5);
	col = smoothstep(diameter, diameter - smoothness, col);
		    
	return col;
}
			
void main()
{
	vec2 uv = input.uv - 0.5;
	vec3 rayOrigin = input.originPos;
	vec3 rayDirection = normalize(input.hitPos - rayOrigin);

	float distance = rayMarch(rayOrigin, rayDirection);
			
	vec4 col = vec4(0, 0, 0, 1);

	if (distance < MAX_DISTANCE)
	{		
		vec3 point = rayOrigin + rayDirection * distance;
		vec3 normal = getNormal(point);
		col.rgb = normal;
	} else
	{
		discard;
	}

	FragColor = col;
}