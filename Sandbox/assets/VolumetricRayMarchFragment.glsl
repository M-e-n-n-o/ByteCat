#version 330 core

#define MAX_STEPS 500
#define STEP_SIZE 0.015
#define MIN_DISTANCE 0.001
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

uniform float _Time;

uniform vec3 sunPos;
uniform sampler2D noiseTexture;
uniform vec3 points[20];

/* discontinuous pseudorandom uniformly distributed in [-0.5, +0.5]^3 */
vec3 random3(vec3 c) 
{
	float j = 4096.0*sin(dot(c,vec3(17.0, 59.4, 15.0)));
	vec3 r;
	r.z = fract(512.0*j);
	j *= .125;
	r.x = fract(512.0*j);
	j *= .125;
	r.y = fract(512.0*j);
	return r-0.5;
}

const float F3 =  0.3333333;
const float G3 =  0.1666667;
float snoise(vec3 p) 
{

	vec3 s = floor(p + dot(p, vec3(F3)));
	vec3 x = p - s + dot(s, vec3(G3));
	 
	vec3 e = step(vec3(0.0), x - x.yzx);
	vec3 i1 = e*(1.0 - e.zxy);
	vec3 i2 = 1.0 - e.zxy*(1.0 - e);
	 	
	vec3 x1 = x - i1 + G3;
	vec3 x2 = x - i2 + 2.0*G3;
	vec3 x3 = x - 1.0 + 3.0*G3;
	
	vec4 w, d;
	 
	w.x = dot(x, x);
	w.y = dot(x1, x1);
	w.z = dot(x2, x2);
	w.w = dot(x3, x3);
	 
	w = max(0.6 - w, 0.0);
	 
	d.x = dot(random3(s), x);
	d.y = dot(random3(s + i1), x1);
	d.z = dot(random3(s + i2), x2);
	d.w = dot(random3(s + 1.0), x3);
	 
	w *= w;
	w *= w;
	d *= w;
	 
	return dot(d, vec4(52.0));
}

float snoiseFractal(vec3 m) {
	return   0.5333333* snoise(m)
				+0.2666667* snoise(2.0*m)
				+0.1333333* snoise(4.0*m)
				+0.0666667* snoise(8.0*m);
}

float getDistance(vec3 point)
{
//	float distance = length(vec2(length(point.xz) - 1, point.y)) - 0.5;
//	float distance2 = length(point) - 2;
//	return distance;

	return length(point) - 1;
}

vec4 volumetricRayMarch(vec3 rayOrigin, vec3 rayDirection)
{
	float distanceOrigin = 0;

	float distanceInMaterial = 0;
	float lightReached = 0;

	for (int i = 0; i < MAX_STEPS; i++)
	{
		vec3 point = rayOrigin + (distanceOrigin * rayDirection);
		distanceOrigin += STEP_SIZE;

		float distanceSurface = getDistance(point);

		if (distanceSurface < MIN_DISTANCE)
		{
			distanceInMaterial += STEP_SIZE * snoiseFractal(point + vec3(_Time / 20, 0, 0));

			float distancePoint = 0;
			float totalLight = 0;
			vec3 lightDirection = (vec3(point.x, point.y + 1, point.z) - point);

			for (int j = 0; j < LIGHT_MAX_STEPS; j++)
			{
				distancePoint += LIGHT_STEP_SIZE;
				vec3 point2 = point + (distancePoint * lightDirection);

				distanceSurface = getDistance(point2);
				if (distanceSurface > MIN_DISTANCE)
				{
					break;
				}

				lightReached += snoise(point2 + vec3(_Time / 20, 0, 0));
			}

			lightReached += totalLight;
		}

		if (distanceOrigin > MAX_DISTANCE)
		{
			break;
		}
	}

	vec4 color = vec4(0, 0, 0, 0);
	color.a = 1 - (1 / exp(distanceInMaterial * 10));

	color.rgb = vec3(lightReached);

	return color;
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

	vec3 rayOrigin = input.cameraPos;
	vec3 viewDirection = normalize(input.worldPos - input.cameraPos);

	vec4 col = volumetricRayMarch(rayOrigin, viewDirection);

	FragColor = col;
}