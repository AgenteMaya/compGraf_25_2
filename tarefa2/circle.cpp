#include "circle.h"

#include <iostream>

#ifdef _WIN32
#include <glad/glad.h>

#elif __APPLE__
#include <OpenGL/gl3.h>

#elif __linux__
#include <glad/glad.h>
#endif

int nTri = 300;


CirclePtr Circle::Make (glm::vec2 center, float raio)
{
  return CirclePtr(new Circle(center, raio));
}

Circle::Circle ()
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

Circle::Circle(glm::vec2 center, float raio)
{
    float angle = 360.0f / (nTri + 2);

    std::vector<glm::vec2> vertices;
    //vertices.push_back(center);

    for (int i = 0; i < nTri; i++)
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
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glBufferData(GL_ARRAY_BUFFER,vertices.size() * 8, vertices.data(),GL_STATIC_DRAW);
  glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);  // coord
  glEnableVertexAttribArray(0);
}

Circle::~Circle () 
{
}

void Circle::Draw ()
{
  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLE_FAN,0, nTri);
}
