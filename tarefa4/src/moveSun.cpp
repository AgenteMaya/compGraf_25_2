#include "moveSun.h"

#include <iostream>

#ifdef _WIN32
#include <glad/glad.h>

#elif __APPLE__
#include <OpenGL/gl3.h>

#elif __linux__
#include <glad/glad.h>
#endif

MoveSun::MoveSun (TransformPtr trf) 
  : m_trf(trf) 
  {  }
MoveSunPtr MoveSun::Make (TransformPtr trf)
{
    return MoveSunPtr(new MoveSun(trf));
}
void MoveSun::Update (float dt)
{
    std::cout << "entrei n update da moveSun" << std::endl;
    m_trf->Rotate(-dt/30.0f*180.0f,0,0,1);
}