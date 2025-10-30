#version 410

layout(location = 0) in vec4 coord;
layout(location = 1) in vec3 normal;

uniform mat4 Mv; 
uniform mat4 Mn; 
uniform mat4 Mvp;

uniform vec4 lpos;  

out vec3 newNormal;
out vec3 newLight;  
out vec3 newEye;

void main (void) 
{
  vec3 posEye = (Mv * coord).xyz;
  newEye = normalize(-posEye);
  newLight = normalize(lpos.xyz - posEye);
  newNormal = normalize(mat3(Mn) * normal);
  gl_Position = Mvp * coord; 
}
