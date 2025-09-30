#include "moveMoon.h"

#include <iostream>

#ifdef _WIN32
#include <glad/glad.h>

#elif __APPLE__
#include <OpenGL/gl3.h>

#elif __linux__
#include <glad/glad.h>
#endif
#include <glm/gtc/matrix_transform.hpp>

MoveMoon::MoveMoon (TransformPtr trf) 
  : m_trf(trf) 
  {  }
MoveMoonPtr MoveMoon::Make (TransformPtr trf)
{
    return MoveMoonPtr(new MoveMoon(trf));
}
void MoveMoon::Update (float dt)
{
    std::cout << "entrei n update da moveMoon" << std::endl;
    float omega = (glm::two_pi<float>() / 3600.0f) * dt;

    m_trf->Rotate(omega,0,0,-1);
}