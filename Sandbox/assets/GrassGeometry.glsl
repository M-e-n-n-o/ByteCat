#version 450 core

#define LAYERS 10

layout (triangles) in;
layout (triangle_strip, max_vertices = 3 * LAYERS) out;

in v2g
{
    vec2 uv;
} _i[];

out g2f
{
    vec2 uv;
    float height;
} o;

const float distanceBetweenLayer = 0.5;

vec3 getNormal()
{
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(a, b));
}  

vec4 extend(vec4 position, vec3 normal, float magnitude)
{
    vec3 direction = normal * magnitude; 
    return position + vec4(direction, 0.0);
}

void main()
{
    for(int i = 0; i < LAYERS; i++)
    {
        float layers = (LAYERS - 1);
        float height = (i / layers) * distanceBetweenLayer;

        for (int j = 0; j < 3; j++)
        {
            gl_Position = extend(gl_in[j].gl_Position, getNormal(), height);

            o.uv = _i[j].uv;
            o.height = height;

            EmitVertex();
        }

        EndPrimitive();
    }
} 