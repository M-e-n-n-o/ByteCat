#version 330 core

#define MAX_STEPS 1000
#define MIN_DISTANCE 0.001
#define MAX_DISTANCE 100

#define VOLUME_MAX_STEPS 10
#define VOLUME_STEP_SIZE 0.01

in v2f
{
	vec2 uv;
	vec3 cameraPos;
	vec3 worldPos;
} input;

out vec4 FragColor;

uniform sampler2D noiseTexture;

float getDistance(vec3 point)
{
	float distance = length(vec2(length(point.xz) - 1, point.y)) - 0.1;
	float distance2 = length(point) - 1;
	return distance2;
}

float volumetricRayMarch(vec3 rayOrigin, vec3 rayDirection)
{
	float distanceOrigin = 0;
	float distanceSurface = 0;
	float distanceInMaterial = 0;

	for (int i = 0; i < MAX_STEPS; i++)
	{
		vec3 point = rayOrigin + (distanceOrigin * rayDirection);
		distanceOrigin += VOLUME_STEP_SIZE;

		distanceSurface = getDistance(point);
		if (distanceSurface < MIN_DISTANCE || distanceOrigin > MAX_DISTANCE)
		{
			distanceInMaterial += VOLUME_STEP_SIZE;
		}
	}

	float alpha = 0;
	alpha = 1 - (1 / exp(distanceInMaterial * 0.2));

	// You hit a material
//	if (distanceOrigin < MAX_DISTANCE)
//	{
//		float distanceTraveledInMaterial = 0;
//		for (int i = 0; i < VOLUME_MAX_STEPS; i++)
//		{
//			vec3 point = rayOrigin + distanceOrigin * rayDirection;
//			distanceOrigin += VOLUME_STEP_SIZE;
//
//			float distance = getDistance(point);
//			// Still in the material?
//			if (distance < MIN_DISTANCE)
//			{
//				//float volume = texture(noiseTexture, input.uv).r;
//				distanceTraveledInMaterial += VOLUME_STEP_SIZE; // * volume;
//			}
//		}
//
//		alpha = 1 - (1 / exp(distanceTraveledInMaterial * 1));
//	}

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
//	vec2 uv = input.uv - 0.5;
//	vec3 rayOrigin = input.originPos;
//	vec3 rayDirection = normalize(input.hitPos - rayOrigin);

	vec3 viewDirection = normalize(input.worldPos - input.cameraPos);

	vec3 rayOrigin = input.cameraPos;
//	float dist1 = getDistance(input.cameraPos);
//	float dist2 = getDistance(input.worldPos);
//	if (dist1 < dist2)
//	{
//		rayOrigin = input.cameraPos;
//	}
	
	vec4 col = vec4(.5, .5, .5, 0);

	col.a = volumetricRayMarch(rayOrigin, viewDirection);

//	for (int i = 0; i < 64; i++)
//    {
//		float distance = getDistance(worldPosition);
//        if (distance < MIN_DISTANCE)
//        {
//			col.a = 1;
//			break;
//		}
//
//        worldPosition += viewDirection * distance;
//    }

	FragColor = col;
}