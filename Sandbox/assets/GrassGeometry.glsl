#version 450 core

#define LAYERS 5

layout (triangles) in;
layout (triangle_strip, max_vertices = 3 * LAYERS) out;

out float layer;

const float distanceBetweenLayer = 0.2;

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
    for (int i = 0; i < LAYERS; i++)
    {
        gl_Position = extend(gl_in[0].gl_Position, getNormal(), i * distanceBetweenLayer);
        layer = i;
        EmitVertex();

        gl_Position = extend(gl_in[1].gl_Position, getNormal(), i * distanceBetweenLayer);
        layer = i;
        EmitVertex();

        gl_Position = extend(gl_in[2].gl_Position, getNormal(), i * distanceBetweenLayer);
        layer = i;
        EmitVertex();

        EndPrimitive();
    }
} 