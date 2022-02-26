#version 430

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
layout(rgba16f, binding = 0) uniform image3D img_output;

void main() 
{
  // base pixel colour for image
  vec4 pixel = vec4(0.0, 0.0, 0.0, 1.0);
  // get index in global work group i.e x,y position
  ivec3 pixel_coords = ivec3(gl_GlobalInvocationID.xyz);
  
  if (pixel_coords.y > 64)
  {
	pixel.r = 1;
  }

  pixel.g = mod(pixel_coords.z, 2);
  
  // output to a specific pixel in the image
  imageStore(img_output, pixel_coords, pixel);
}