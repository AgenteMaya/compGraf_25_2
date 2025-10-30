#version 410

in vec3 newNormal;
in vec3 newLight;  
in vec3 newEye;

uniform vec4 mamb;
uniform vec4 mdif;
uniform vec4 mspe;
uniform float mshi;

uniform vec4 lamb;
uniform vec4 ldif;
uniform vec4 lspe;

out vec4 fcolor;

void main (void)
{
  vec3 N = normalize(newNormal);
  vec3 L = normalize(newLight);
  vec3 E = normalize(newEye);

  float NdotL = max(dot(N, L), 0.0);
  vec4 dif = NdotL * mdif * ldif;
  vec3 R = reflect(-L, N);
  float spec = pow(max(dot(R, E), 0.0), mshi);
  vec4 spe = spec * mspe * lspe;
  fcolor = mamb * lamb + dif + spe;
}
