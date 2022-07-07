#version 450 core

#define MAX_STEPS 100
#define MIN_DISTANCE 0.001
#define MAX_DISTANCE 100
			
in v2f
{
	vec2 uv;
	vec3 originPos;
	vec3 hitPos;	
} i;

uniform float _time;

out vec4 FragColor;

float getDistance(vec3 point)
{
//	float distance = length(vec2(length(point.xz) - 0.5, point.y)) - 0.1;
//
//	float distanceCircle = length(point - vec3(0, 0, 0)) - 0.5;
//
//	return max(-distance, distanceCircle);

	point = point - vec3(0, 50, 0);

	const float Bailout = 2;

	float power = 10 * (sin(_time / 15) * 3);

	vec3 z = point;
	float dr = 1.0;
	float r = 0.0;
	for (int i = 0; i < 15 ; i++) 
	{
		r = length(z);

		if (r>Bailout) break;
		
		// convert to polar coordinates
		float theta = acos(z.z / r);
		float phi = atan(z.y, z.x);
		dr =  pow( r, power - 1.0) * power * dr + 1.0;
		
		// scale and rotate the point
		float zr = pow( r, power);
		theta = theta * power;
		phi = phi*power;
		
		// convert back to cartesian coordinates
		z = zr * vec3(sin(theta) * cos(phi), sin(phi) * sin(theta), cos(theta));
		z += point;
	}

	return 0.1 * log(r) * r / dr;
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
	vec2 uv = i.uv - 0.5;
	vec3 rayOrigin = i.originPos;
	vec3 rayDirection = normalize(i.hitPos - i.originPos);
	
	vec4 col = vec4(1, 1, 1, 1);

	float distance = rayMarch(rayOrigin, rayDirection);
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