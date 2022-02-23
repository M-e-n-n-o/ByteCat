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
uniform vec3 points[3];

float getDistance(vec3 point)
{
//	float distance = length(vec2(length(point.xz) - 0.5, point.y)) - 0.1;
//
//	float distanceCircle = length(point - vec3(0, 0, 0)) - 0.5;
//
//	return max(-distance, distanceCircle);


	float closest = 1000;
	for (int i = 0; i < 3; i++)
	{
		float d = length(point - points[i]);
		closest = min(closest, d);
	}

	return closest - 0.01;
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

void main()
{
	vec2 uv = input.uv - 0.5;
	vec3 rayOrigin = input.originPos;
	vec3 rayDirection = normalize(input.hitPos - rayOrigin);
	
	vec4 col = vec4(0, 0, 0, 1);

	float distance = rayMarch(rayOrigin, rayDirection);
	if (distance < MAX_DISTANCE)
	{
		vec3 point = rayOrigin + rayDirection * distance;
		vec3 normal = getNormal(point);
		col.rgb = normal;
	} else
	{
		//discard;
	}

	FragColor = col;
}