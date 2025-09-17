#include "triangle.h"

#include <iostream>

#ifdef _WIN32
#include <glad/glad.h>

#elif __APPLE__
#include <OpenGL/gl3.h>

#elif __linux__
#include <glad/glad.h>
#endif

TrianglePtr Triangle::Make (std::vector<glm::vec2> coord)
{
  return TrianglePtr(new Triangle(coord));
}

Triangle::Triangle ()
{
  float coord[] = {
    -0.5f,-0.5f, 
     0.5f,-0.5f,
     0.0f, 0.5f,
  };
  unsigned char color[] = {
    255, 0, 0,
    0, 255, 0,
    0, 0, 255
  };
  // create VAO
  glGenVertexArrays(1,&m_vao);
  glBindVertexArray(m_vao);
  // create coord buffer
  GLuint id[2];
  glGenBuffers(2,id);
  glBindBuffer(GL_ARRAY_BUFFER,id[0]);
  glBufferData(GL_ARRAY_BUFFER,sizeof(coord),coord,GL_STATIC_DRAW);
  glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);  // coord
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER,id[1]);
  glBufferData(GL_ARRAY_BUFFER,sizeof(color),color,GL_STATIC_DRAW);
  glVertexAttribPointer(1,3,GL_UNSIGNED_BYTE,GL_TRUE,0,0);  // color
  glEnableVertexAttribArray(1);
}

Triangle::Triangle(std::vector<glm::vec2> coord)
{
  // create VAO
  glGenVertexArrays(1,&m_vao);
  glBindVertexArray(m_vao);
  // create coord buffer
  GLuint id;
  glGenBuffers(1,&id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  std::cout << coord.size() << std::endl;
  glBufferData(GL_ARRAY_BUFFER,coord.size() * 8, coord.data(),GL_STATIC_DRAW);
  glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);  // coord
  glEnableVertexAttribArray(0);
}

Triangle::~Triangle () 
{
}

void Triangle::Draw ()
{
  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLES,0,3);
}