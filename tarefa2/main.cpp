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


#include "error.h"
#include "triangle.h"
#include "circle.h"
#include "shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

static TrianglePtr triH;
static TrianglePtr triMin;
static TrianglePtr triSeg;
static CirclePtr circ;
static ShaderPtr shd;

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
     {0.0f, 0.5f},
  };

  std::vector<glm::vec2> coordMin = {
     {-0.015f,0}, 
     {0.015f, 0},
     {0.0f, 0.7f},
  };
  std::vector<glm::vec2> coordSeg = {
     {-0.005f,0}, 
     {0.005f, 0},
     {0.0f, 0.7f},
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
  Error::Check("initialize");
}

void update(float dt)
{
  
}

static void display (GLFWwindow* win, float t0)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shd->UseProgram();

  auto t = glfwGetTime();

  update(t - t0);

  glm::vec4 colorC = {0.678f, 0.847f, 0.902f, 1.0f};
  shd->SetUniform("color", colorC);
  circ->Draw();
  shd->SetUniform("color", glm::vec4{1,0,0,1});
  triMin->Draw();
  shd->SetUniform("color", glm::vec4{0,0,0,1});
  triH->Draw();
  shd->SetUniform("color", glm::vec4{0,0,0,1});
  triSeg->Draw();
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

  GLFWwindow* win = glfwCreateWindow(500,500,"Circle test",nullptr,nullptr);
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

   auto t0 = glfwGetTime() ;
  while(!glfwWindowShouldClose(win)) {
    //idle(win);
    display(win, t);
    glfwSwapBuffers(win);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
