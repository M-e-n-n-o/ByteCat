#version 430 core

#define NEAR 0.1f
#define FAR 1000.0f

out vec4 fragColor;
  
in v2f
{
    vec2 uv;
	vec3 cameraPos;
    vec3 viewVector;
} i;

uniform sampler3D cloudNoise;
uniform sampler2D screenTexture;
uniform sampler2D depthTexture;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float numStepsLight;
uniform float lightAbsorptionThroughCloud;
uniform float lightAbsorptionTowardSun;
uniform float darknessThreshold;
uniform float edgeFadeDistance;

uniform vec3 boxMin;
uniform vec3 boxMax;
uniform float numSteps;
uniform vec3 cloudOffset;
uniform float cloudScale;
uniform float densityThreshold;
uniform float densityMultiplier;

float linearizeDepth(float d,float zNear,float zFar)
{
    return zNear * zFar / (zFar + d * (zNear - zFar));
}

float sampleDensity(vec3 point)
{
	vec3 uvw = point * cloudScale * 0.001 + cloudOffset * 0.01;
	vec4 shape = texture(cloudNoise, uvw);
	float density = (max(0, shape.r - densityThreshold) * densityMultiplier);

	// Fade away at the corners of the box
    float dstFromEdgeX = min(edgeFadeDistance, min(point.x - boxMin.x, boxMax.x - point.x));
	float dstFromEdgeY = min(edgeFadeDistance, min(point.y - boxMin.y, boxMax.y - point.y));
    float dstFromEdgeZ = min(edgeFadeDistance, min(point.z - boxMin.z, boxMax.z - point.z));
    float edgeWeight = min(min(dstFromEdgeX, dstFromEdgeY), dstFromEdgeZ) / edgeFadeDistance;

	return density * edgeWeight;
}

// x = distanceToBox, y = distinceFromFrontToBackOfBox
vec2 rayBoxDist(vec3 boundsMin, vec3 boundsMax, vec3 rayOrigin, vec3 rayDir)
{
	vec3 t0 = (boundsMin - rayOrigin) / rayDir;
	vec3 t1 = (boundsMax - rayOrigin) / rayDir;
	vec3 tmin = min(t0, t1);
	vec3 tmax = max(t0, t1);

	float dstA = max(max(tmin.x, tmin.y), tmin.z);
	float dstB = min(tmax.x, min(tmax.y, tmax.z));

	float dstToBox = max(0, dstA);
	float dstInsideBox = max(0, dstB - dstToBox);
	return vec2(dstToBox, dstInsideBox);
}

float lightMarch(vec3 point)
{
	vec3 toLight = normalize(lightPos - point);
	float dstInsideBox = rayBoxDist(boxMin, boxMax, point, 1 / toLight).y;

	float stepSize = dstInsideBox / numStepsLight;
	float totalDensity = 0;

	for (int step = 0; step < numStepsLight; step++)
	{
		point += toLight * stepSize;
		totalDensity += max(0, sampleDensity(point) * stepSize);
	}

	float transmittance = exp(-totalDensity * lightAbsorptionTowardSun);
	return darknessThreshold + transmittance * (1 - darknessThreshold);
}

void main()
{
	vec3 ro = i.cameraPos;
	vec3 rd = normalize(i.viewVector);

	float depth = linearizeDepth(texture(depthTexture, i.uv).r, NEAR, FAR);

	vec2 rayBoxInfo = rayBoxDist(boxMin, boxMax, ro, rd);
	float dstToBox = rayBoxInfo.x;
	float dstInsideBox = rayBoxInfo.y;

	float dstTravelled = 0;
	float stepSize = dstInsideBox / numSteps;
	float dstLimit = min(depth - dstToBox, dstInsideBox);

	float totalDensity = 0;
	float transmittance = 1;
	vec3 lightEnergy = vec3(0);

	// Stop when you hit the end of the box or hit something else in the scene
	while (dstTravelled < dstLimit)
	{
		vec3 rayPos = ro + rd * (dstToBox + dstTravelled);

		float density = sampleDensity(rayPos);

		// Is there a cloud at this point?
		if (density > 0)
		{
			float lightTransmittance = lightMarch(rayPos);
			lightEnergy += density * stepSize * transmittance * lightTransmittance;
			transmittance *= exp(-density * stepSize * lightAbsorptionThroughCloud);

			if (transmittance < 0.01)
			{
				break;
			}
		}

		totalDensity += density;
		dstTravelled += stepSize;
	}

	vec3 screenColor = texture(screenTexture, i.uv).rgb;
	screenColor *= 2; // Color correction

	vec3 cloudColor = lightEnergy * lightColor;

	vec3 col = mix(screenColor, cloudColor, 0.5) * transmittance;
	fragColor = vec4(col, 1);
}