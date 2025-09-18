#version 410

layout (location=0) in vec4 vertex;
uniform mat4 M;

void main (void)
{
  gl_Position = M * vertex;
}

