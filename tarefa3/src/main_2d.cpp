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

#include "scene.h"
#include "state.h"
#include "camera2d.h"
#include "color.h"
#include "transform.h"
#include "error.h"
#include "shader.h"
#include "quad.h"
#include "triangle.h"
#include "disk.h"
/* #include "moveEarth.h"
#include "moveMoon.h"
#include "moveSun.h" */

#include <iostream>

static ScenePtr scene;
static CameraPtr camera;

class MovePointer;
using MovePointerPtr = std::shared_ptr<MovePointer>;
class MovePointer : public Engine 
{
  TransformPtr m_trf;
protected:
  MovePointer (TransformPtr trf) 
  : m_trf(trf) 
  {
  }
public:
  static MovePointerPtr Make (TransformPtr trf)
  {
    return MovePointerPtr(new MovePointer(trf));
  }
  virtual void Update (float dt)
  {
    m_trf->Rotate(-dt/30.0f*180.0f,0,0,1);
  }
};

static void initialize (void)
{
  // set background color: white 
  glClearColor(0,0,0,0);
  // enable depth test 
  glEnable(GL_DEPTH_TEST);
  // create objects
  camera = Camera2D::Make(0,10,0,10);  
  /* auto trf1 = Transform::Make();
  trf1->Translate(3.0f,3.0f,-0.5f);
  trf1->Scale(4.0f,4.0f,1.0f);
  auto face = Node::Make(trf1,{Color::Make(1,1,1)},{Quad::Make()});
  auto trf2 = Transform::Make();
  trf2->Translate(5.0f,5.0f,0.0f);
  auto trf3 = Transform::Make();
  trf3->Scale(0.1f,2.0f,1.0f);
  auto pointer = Node::Make(trf2,{Node::Make(trf3,{Color::Make(1,0,0)},{Triangle::Make()})}); */


  auto trfMoon = Transform::Make();
  trfMoon->Scale(0.4, 0.4, 1.0);
  trfMoon->Translate(8,8,0);
  auto faceMoon = Node::Make(trfMoon, {Color::Make(1,1,1)}, {Disk::Make(300)});
  //auto faceMoon = Node::Make(trfEarth, {Node::Make(trfMoon, {Color::Make(1,1,1)}, {Disk::Make(300)})});
 
  auto trfEarth = Transform::Make();
  trfEarth->Scale(0.5, 0.5, 1.0);
  trfEarth->Translate(8,8,0);
  auto faceEarth = Node::Make(trfEarth, {Color::Make(0,0,1)}, {Disk::Make(300)}, {faceMoon});
  //auto faceEarth = Node::Make(trfSun, {Node::Make(trfEarth, {Color::Make(0,0,1)}, {Disk::Make(300)})});



  //auto sun = Disk::Make(300);
  auto trfSun = Transform::Make();
  trfSun->Scale(0.6, 0.6, 1.0);
  trfSun->Translate(9,8,0);
  auto faceSun = Node::Make(trfSun, {Color::Make(1,1,0)}, {Disk::Make(300)}, {faceEarth});

  
 


  auto shader = Shader::Make();
  shader->AttachVertexShader("/home/mayara/Documentos/periodos/8periodo/compGraf_25_2/tarefa3/shaders/2d/vertex.glsl");
  shader->AttachFragmentShader("/home/mayara/Documentos/periodos/8periodo/compGraf_25_2/tarefa3/shaders/2d/fragment.glsl");
  shader->Link();
  // build scene
  /* auto root = Node::Make(shader, {face,pointer});
  scene = Scene::Make(root);
  scene->AddEngine(MovePointer::Make(trf2)); */

  auto root = Node::Make(shader, {faceSun});
  scene = Scene::Make(root);
  scene->AddEngine(MovePointer::Make(trfEarth));
  //scene->AddEngine(MovePointer::Make(trfMoon));
  scene->AddEngine(MovePointer::Make(trfSun));
}

static void display (GLFWwindow* win)
{ 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window 
  Error::Check("before render");
  scene->Render(camera);
  Error::Check("after render");
}

static void error (int code, const char* msg)
{
  printf("GLFW error %d: %s\n", code, msg);
  glfwTerminate();
  exit(0);
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

static void update (float dt)
{
  scene->Update(dt);
}

int main ()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);       // required for mac os
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);  // option for mac os
#endif
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE); 
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwSetErrorCallback(error);
    GLFWwindow* win = glfwCreateWindow(600, 400, "Sun, Earth and Moon system", nullptr, nullptr);
    assert(win);
    glfwSetFramebufferSizeCallback(win, resize);  // resize callback
    glfwSetKeyCallback(win, keyboard);            // keyboard callback

    glfwMakeContextCurrent(win);

  #ifdef __glad_h_
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD OpenGL context\n");
    exit(1);
   }
  #endif


glEnable(GL_MULTISAMPLE);
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

  initialize();
  float t0 = float(glfwGetTime());
  while(!glfwWindowShouldClose(win)) {
    float t = float(glfwGetTime());
    update(t-t0);
    t0 = t;
    display(win);
    glfwSwapBuffers(win);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}

