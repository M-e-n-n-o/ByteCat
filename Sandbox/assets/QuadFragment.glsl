#version 430 core

#define MAX_STEPS 100
#define MAX_DISTANCE 1000
#define MIN_DISTANCE 0.01

out vec4 fragColor;
  
in v2f
{
    vec2 uv;
    vec3 viewVector;
} input;

uniform vec3 _cameraPos;
uniform sampler2D screenTexture;

vec2 rayBoxDist(vec3 boundsMin, vec3 boundsMax, vec3 ro, vec3 rd)
{
    vec3 t0 = (boundsMin - ro) / rd;
    vec3 t1 = (boundsMax - ro) / rd;
    vec3 tmin = min(t0, t1);
    vec3 tmax = max(t0, t1);

    float distA = max(max(tmin.x, tmin.y), tmin.z);
    float distB = min(tmax.x, min(tmax.y, tmax.z));

    float distToBox = max(0, distA);
    float distInsideBox = max(0, distB - distToBox);
    return vec2(distToBox, distInsideBox);
}

float getDistance(vec3 point)
{
    //return length(point - vec3(0, -1, 5)) - 2;

	point += vec3(0, 0, 3);

	return length(vec2(length(point.xz) - 0.2, point.y)) - 0.1;
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
	vec3 ro = _cameraPos;
	float viewLength = length(input.viewVector);
	vec3 rd = input.viewVector / viewLength;

	vec4 col = vec4(vec3(0), 1);

    vec2 rayBoxInfo = rayBoxDist(vec3(0, 0, 0), vec3(10, 10, 10), ro, rd);
    float distToBox = rayBoxInfo.x;
    float distInsideBox = rayBoxInfo.y;

    bool rayHitBox = distInsideBox > 0;
    if (rayHitBox)
    {
        col.rgb = texture(screenTexture, input.uv).rgb;
    }

	fragColor = col;
}