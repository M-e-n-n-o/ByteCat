#version 450 core

out vec4 fragColor;

in g2f
{
    vec2 uv;
    float height;
} i;

uniform float _time;

uniform sampler2D noise;
uniform sampler2D windNoise;

const float detailNoiseScale = 1;
const float detailDepthScale = 1;

const float smoothNoiseScale = 0.03;
const float smoothDepthScale = 1;

const vec3 baseColor = vec3(0, 0.1, 0);
const vec3 topColor = vec3(0, 1, 0);

const float windScale = 0.01;
const float windTimeMult = 0.002;
const float windAmplitude = 0.1;

void main()
{
    vec2 windUV = (i.uv * windScale) + _time * windTimeMult;
    vec2 windNoise = texture(windNoise, windUV).xy * 2 - 1;
    vec2 uv = i.uv.xy + windNoise * (windAmplitude * i.height);

    float detailNoise = texture(noise, uv * detailNoiseScale).r;
    float smoothNoise = texture(noise, uv * smoothNoiseScale).r;

    detailNoise = 1 - (1 - detailNoise) * detailDepthScale;
    smoothNoise = 1 - (1 - smoothNoise) * smoothDepthScale;

    if (detailNoise * smoothNoise - i.height < 0)
    {
        discard;
    }
                
    fragColor = vec4(mix(baseColor, topColor, i.height).rgb, 1);
}