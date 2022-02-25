#version 330 core

#define MAX_STEPS 100
#define MIN_DISTANCE 0.001
#define MAX_DISTANCE 100

#define VOLUME_MAX_STEPS 100
#define VOLUME_STEP_SIZE 0.01
			
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
	float distance = length(vec2(length(point.xz) - 0.5, point.y)) - 0.1;
	float distance2 = length(point) - 0.5;
	return max(-distance, distance2);
}

float volumetricRayMarch(vec3 rayOrigin, vec3 rayDirection)
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

	float alpha = 0;

	// You hit a material
	if (distanceOrigin < MAX_DISTANCE)
	{
		float distanceTraveledInMaterial = 0;
		for (int i = 0; i < VOLUME_MAX_STEPS; i++)
		{
			vec3 point = rayOrigin + distanceOrigin * rayDirection;
			distanceOrigin += VOLUME_STEP_SIZE;

			float distance = getDistance(point);
			// Still in the material?
			if (distance < MIN_DISTANCE)
			{
				//float volume = texture(noiseTexture, input.uv).r;
				distanceTraveledInMaterial += VOLUME_STEP_SIZE; // * volume;
			}
		}

		alpha = 1 - (1 / exp(distanceTraveledInMaterial));
	}

	return alpha;
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
	
	vec4 col = vec4(.5, .5, .5, 1);

	col.a = volumetricRayMarch(rayOrigin, rayDirection);

	FragColor = col;
}