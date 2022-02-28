#version 430 core

#define NEAR 0.1f
#define FAR 1000.0f

#define MAX_STEPS 100
#define STEP_SIZE 0.01
#define MAX_DISTANCE 1000
#define MIN_DISTANCE 0.01

out vec4 fragColor;
  
in v2f
{
    vec2 uv;
	vec3 cameraPos;
    vec3 viewVector;
} input;

uniform sampler3D cloudNoise;
uniform sampler2D screenTexture;
uniform sampler2D depthTexture;

uniform vec3 boxPos;
uniform vec3 boxScale;
uniform vec3 cloudOffset;
uniform float cloudScale;
uniform float densityThreshold;
uniform float densityMultiplier;

float dBox(vec3 point, vec3 scale)
{
	return length(max(abs(point) - scale, 0));
}

float getDistance(vec3 point)
{
	return dBox(point + (vec3(boxPos)), vec3(boxScale));
}

float sampleDensity(vec3 point)
{
	vec3 uvw = point * cloudScale * 0.001 + cloudOffset * 0.01;
	vec4 shape = texture(cloudNoise, uvw);
	return max(0, shape.r - densityThreshold) * densityMultiplier;
}

// x = alpha, y = distance
vec2 rayMarch(vec3 ro, vec3 rd)
{
	float dO = 0;
	float dS = 0;
	float dstInMat = 0;

	for (int i = 0; i < MAX_STEPS; i++)
	{
		vec3 point = ro + dO * rd;
		dS = getDistance(point);
		dO += STEP_SIZE;

		if (dS < MIN_DISTANCE)
		{
			dstInMat += STEP_SIZE * sampleDensity(point);
		}

		if (dO > MAX_DISTANCE)
		{
			break;
		}
	}

	float alpha = 1 - (1 / exp(dstInMat));

	return vec2(alpha, dO);
}

float linearizeDepth(float d,float zNear,float zFar)
{
    return zNear * zFar / (zFar + d * (zNear - zFar));
}

void main()
{
	vec3 ro = input.cameraPos;
	vec3 rd = normalize(input.viewVector);

	float depth = linearizeDepth(texture(depthTexture, input.uv).r, NEAR, FAR);

	vec4 col = texture(screenTexture, input.uv);

	vec2 info = rayMarch(ro, rd);
	float alpha = info.x;
	float distance = info.y;

	if (distance < MAX_DISTANCE && distance < depth)
	{
		col.rgb = vec3(0);
	}

	fragColor = col;
}