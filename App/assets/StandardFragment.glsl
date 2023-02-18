#version 450 core

in VS_OUT
{
	vec3 pos;
    vec3 normal;
    vec2 uv;
    vec4 fragPosLightSpace;
} fs_in;

out vec4 fragColor;

uniform sampler2D mainTexture;
uniform sampler2D _shadowMap;

uniform vec3 _cameraPos;
uniform vec3 _mainLightSourcePos;

uniform float biasStandard;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(_shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    vec3 normal = normalize(fs_in.normal);
    vec3 lightDir = normalize(_mainLightSourcePos - fs_in.pos);
    float bias = max((biasStandard * 10) * (1.0 - dot(normal, lightDir)), biasStandard);
    // check whether current frag pos is in shadow
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

void main()
{
	vec3 color = texture(mainTexture, fs_in.uv).rgb;
    vec3 normal = normalize(fs_in.normal);
    vec3 lightColor = vec3(1.0);
    // ambient
    vec3 ambient = 0.15 * lightColor;
    // diffuse
    vec3 lightDir = normalize(_mainLightSourcePos - fs_in.pos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(_cameraPos - fs_in.pos);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;    
    // calculate shadow
    float shadow = ShadowCalculation(fs_in.fragPosLightSpace);     
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    fragColor = vec4(lighting, 1.0);
}