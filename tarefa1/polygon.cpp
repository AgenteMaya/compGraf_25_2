#include "polygon.h"
#include <iostream>

#ifdef _WIN32
#include <glad/glad.h>

#elif __APPLE__
#include <OpenGL/gl3.h>

#elif __linux__
#include <glad/glad.h>
#endif

PolygonPtr Polygon::Make()
{
    return PolygonPtr(new Polygon());
}

Polygon::Polygon()
{
    float coord[] = {
        0.685f, 0.202500f, 
        0.736667f, 0.060f,
        0.530f, 0.49250f,
        0.310f, 0.5850f,
        0.335f, 0.5850f,
    };
    unsigned char color[] = {
        153, 51, 153,
        255, 255, 0,
        255, 0, 0,
        0, 0, 255,
        0, 255, 0,
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

Polygon::~Polygon () 
{
}

void Polygon::Draw ()
{
  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLE_FAN,0,3);
}