#include "moveEarth.h"

#include <iostream>

#ifdef _WIN32
#include <glad/glad.h>

#elif __APPLE__
#include <OpenGL/gl3.h>

#elif __linux__
#include <glad/glad.h>
#endif

MoveEarth::MoveEarth (TransformPtr trf) 
  : m_trf(trf) 
  {  }
MoveEarthPtr MoveEarth::Make (TransformPtr trf)
{
    return MoveEarthPtr(new MoveEarth(trf));
}
void MoveEarth::Update (float dt)
{
    std::cout << "entrei n update da moveEarth" << std::endl;
    m_trf->Rotate(-dt/30.0f*180.0f,0,0,1);
}