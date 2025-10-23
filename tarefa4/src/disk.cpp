#include "disk.h"

#include <iostream>

#ifdef _WIN32
#include <glad/glad.h>

#elif __APPLE__
#include <OpenGL/gl3.h>

#elif __linux__
#include <glad/glad.h>
#endif
DiskPtr Disk::Make (int nslice)
{

  return DiskPtr(new Disk(nslice));
}

Disk::Disk (int nslice) : m_nslice(nslice)
{
    float angle = 360.0f / (nslice + 2);
    float raio = 1.0f;

    std::vector<glm::vec2> vertices;
    //vertices.push_back(glm::vec2(0.0, 0.0));

    for (int i = 0; i < nslice; i++)
    {
        float currentAngle = angle * i;
        float x = raio * cos(glm::radians(currentAngle));
        float y = raio * sin(glm::radians(currentAngle));
        vertices.push_back(glm::vec2(x, y));
    }

  // create VAO
  glGenVertexArrays(1,&m_vao);

  glBindVertexArray(m_vao);

  // create coord buffer
  GLuint id;

  glGenBuffers(1,&id);

  glBindBuffer(GL_ARRAY_BUFFER,id);

  glBufferData(GL_ARRAY_BUFFER,vertices.size() * 8,vertices.data(),GL_STATIC_DRAW);

  glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);  // coord

  glEnableVertexAttribArray(0);

}

Disk::~Disk () 
{
}

void Disk::Draw (StatePtr )
{
  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLE_FAN,0, m_nslice);
}