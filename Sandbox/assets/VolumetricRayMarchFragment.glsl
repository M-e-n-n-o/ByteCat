#version 330 core

#define MAX_STEPS 1000
#define STEP_SIZE 0.0015
#define MIN_DISTANCE 0.01
#define MAX_DISTANCE 100

#define LIGHT_MAX_STEPS 50
#define LIGHT_STEP_SIZE 0.01

in v2f
{
	vec2 uv;
	vec3 cameraPos;
	vec3 worldPos;
} input;

out vec4 FragColor;

uniform float _time;

uniform vec3 sunPos;
uniform sampler3D noiseTexture;

float getDistance(vec3 point)
{
//	float distance = length(vec2(length(point.xz) - 1, point.y)) - 0.5;
//	float distance2 = length(point) - 2;
//	return distance;

//	return length(point) - 0.1;

	point = abs(point) - vec3(1);
	return length(max(point, 0.5)) + min(max(point.x, max(point.y, point.z)), 0.5);
}

float map(float value, float min1, float max1, float min2, float max2) 
{
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

vec4 volumetricRayMarch(vec3 rayOrigin, vec3 rayDirection)
{
	float distanceOrigin = 0;

	float density = 0.1;

//	float distanceInMaterial = 0;
//	float lightReached = 0;

	for (int i = 0; i < MAX_STEPS; i++)
	{
		vec3 point = rayOrigin + (distanceOrigin * rayDirection);
		distanceOrigin += STEP_SIZE;

		float distanceSurface = getDistance(point);

		if (distanceSurface < MIN_DISTANCE)
		{
			float x = point.x;
			float y = point.y;
			float z = point.z;
			density += texture(noiseTexture, vec3(x, y, z)).r;

//			distanceInMaterial += STEP_SIZE * snoiseFractal(point + vec3(_time / 20, 0, 0));
//
//			float distancePoint = 0;
//			float totalLight = 0;
//			vec3 lightDirection = (vec3(point.x, point.y + 1, point.z) - point);
//
//			for (int j = 0; j < LIGHT_MAX_STEPS; j++)
//			{
//				distancePoint += LIGHT_STEP_SIZE;
//				vec3 point2 = point + (distancePoint * lightDirection);
//
//				distanceSurface = getDistance(point2);
//				if (distanceSurface > MIN_DISTANCE)
//				{
//					break;
//				}
//
//				lightReached += snoise(point2 + vec3(_time / 20, 0, 0));
//			}
//
//			lightReached += totalLight;
		}

		if (distanceOrigin > MAX_DISTANCE)
		{
			break;
		}
	}

	vec4 color = vec4(1, 1, 1, 0);
	color.a = 1 - (1 / exp(density));
	//color.a = density;

	//color.rgb = vec3(lightReached);

	return color;
}

//vec3 getNormal(vec3 point)
//{
//	vec2 epsilon = vec2(0.01, 0);
//
//	vec3 normal = getDistance(point) - vec3(
//		getDistance(point - epsilon.xyy),
//		getDistance(point - epsilon.yxy),
//		getDistance(point - epsilon.yyx)
//		);
//
//	return normalize(normal);
//}

void main()
{
	vec3 rayOrigin = input.cameraPos;
	vec3 viewDirection = normalize(input.worldPos - input.cameraPos);

	vec4 col = volumetricRayMarch(rayOrigin, viewDirection);

	FragColor = col;
}