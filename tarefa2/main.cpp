#ifdef _WIN32
#include <windows.h>
// Use glad to initialize OpenGL context on Windows
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#elif __APPLE__
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#elif __linux__
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#endif

#include <glm/gtc/matrix_transform.hpp>

#include "error.h"
#include "triangle.h"
#include "circle.h"
#include "shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>

static TrianglePtr triH;
static TrianglePtr triMin;
static TrianglePtr triSeg;
static CirclePtr circ;
static ShaderPtr shd;

glm::mat4 M;

static void error (int code, const char* msg)
{
  printf("GLFW error %d: %s\n", code, msg);
  glfwTerminate();
  exit(1);
}

static void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void resize (GLFWwindow* win, int width, int height)
{
  glViewport(0,0,width,height);
}

static void initialize ()
{
  std::vector<glm::vec2> coordH = {
     {-0.015f,0}, 
     {0.015f, 0},
     {0.0f, 0.45f},
  };

  std::vector<glm::vec2> coordMin = {
     {-0.015f,0}, 
     {0.015f, 0},
     {0.0f, 0.65f},
  };
  std::vector<glm::vec2> coordSeg = {
     {-0.005f,0}, 
     {0.005f, 0},
     {0.0f, 0.65f},
  };

  glClearColor(1.0f,1.0f,1.0f,1.0f);
  triH = Triangle::Make(coordH);
  triMin = Triangle::Make(coordMin);
  triSeg = Triangle::Make(coordSeg);
  circ = Circle::Make({0.0, 0.0}, 0.8);
  shd = Shader::Make();
  shd->AttachVertexShader("shaders/vertex.glsl");
  shd->AttachFragmentShader("shaders/fragment.glsl");
  shd->Link();

  int vp[ 4 ] ;
  glGetIntegerv (GL_VIEWPORT, vp);
  float w = (float) vp [2];
  float h = (float) vp [3];
  float xmax = 1, ymax = 1, xmin = -1, ymin = -1;

  auto dx = xmax - xmin;
  auto dy = ymax - ymin;
  if (w/h > dx/dy)
  {
    auto xc = (xmin + xmax)/2;
    xmin = xc - dx/2 * w/h;
    xmax = xc + dx/2 * w/h;
  }
  else
  {
    auto yc = (ymin + ymax)/2;
    ymin = yc - dy/2 * h/w;
    ymax = yc + dy/2 * h/w;
  }

  M = glm::ortho(xmin, xmax, ymin, ymax);

  Error::Check("initialize");
}

void setRotation(float omega)
{
  glm::mat4 MR (1.0f);
  MR = MR * M;
  MR = glm::rotate(MR, omega, glm::vec3{0,0,-1});
  shd->SetUniform("M", MR);
}


void update(float dt)
{

  glm::vec4 colorC = {0.678f, 0.847f, 0.902f, 1.0f};
  shd->SetUniform("color", colorC);
  shd->SetUniform("M", M);
  circ->Draw();

  float omegaMin = (glm::two_pi<float>() / 3600.0f) * dt;
  setRotation(omegaMin);
  shd->SetUniform("color", glm::vec4{1,0,0,1});
  triMin->Draw();

  float omegaH = (glm::two_pi<float>() / 43200.0f) * dt;
  setRotation(omegaH);
  shd->SetUniform("color", glm::vec4{0,0,0,1});
  triH->Draw();

  float omegaS = glm::two_pi<float>() / 60.0f * dt;
  setRotation(omegaS);
  shd->SetUniform("color", glm::vec4{0,0,0,1});
  triSeg->Draw();
}

static void display (GLFWwindow* win, float t0, const float &secInicio)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shd->UseProgram();

  auto t = glfwGetTime();
  update(t - t0 + secInicio);

  Error::Check("display");
}

int main ()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);       // required for mac os
  //glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER,GLFW_TRUE);  // option for mac os
  glfwWindowHint(GLFW_SAMPLES, 4);

  glfwSetErrorCallback(error);

  GLFWwindow* win = glfwCreateWindow(600,400,"Relógio",nullptr,nullptr);
  glfwSetFramebufferSizeCallback(win, resize);  // resize callback
  glfwSetKeyCallback(win, keyboard);            // keyboard callback
  
  glfwMakeContextCurrent(win);
 
#ifdef __glad_h_
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD OpenGL context\n");
    exit(1);
   }
#endif
#ifdef __glew_h__
  glewInit(); 
  if (glewInit() != GLEW_OK) {
    printf("Failed to initialize GLEW OpenGL context\n");
    exit(1);
  }
#endif

  glEnable(GL_MULTISAMPLE);

  printf("OpenGL version: %s\n", glGetString(GL_VERSION));

  initialize();


  time_t t = time(0);
  tm* tReal = localtime(&t);
  auto secInicio = tReal->tm_sec + tReal->tm_min * 60 + tReal->tm_hour * 3600;

  auto t0 = glfwGetTime();
  while(!glfwWindowShouldClose(win)) {
    //idle(win);
    display(win, t0, static_cast<float>(secInicio));
    glfwSwapBuffers(win);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
