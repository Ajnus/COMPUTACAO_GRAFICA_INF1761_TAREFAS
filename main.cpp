#include "error.h"
#include "glad.h"
#include "triangle.h"
#include "shader.h"
#include "disk.h"
#include "polygon.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

static ShaderPtr shd;
static PolygonPtr pol;
static DiskPtr dsk;

static void initialize()
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  shd = Shader::Make();
  shd->AttachVertexShader("shaders/vertex.glsl");
  shd->AttachFragmentShader("shaders/fragment.glsl");
  shd->Link();

  float xy[] = {
      -0.5f,
      -0.5f,
      -0.6f,
      0.5f,
      -0.15f,
      0.2f,
      0.5f,
      0.5f,
      0.3f,
      -0.4f,
  };

  unsigned char rgb[] = {
      100, 0, 0,
      0, 100, 0,
      0, 0, 100,
      100, 100, 0,
      0, 0, 100};

  unsigned int indices[] = {
      0, 1, 2,
      /*0, 2,*/ 3,
      /*0, 3,*/ 4};

  pol = Polygon::Make(5, xy, rgb, indices);
  if (!pol)
  {
    std::cerr << "Erro ao criar o polígono." << std::endl;
    exit(1);
  }

  dsk = Disk::Make();
  if (!dsk)
  {
    std::cerr << "Erro ao criar o(s) disco(s)." << std::endl;
    exit(1);
  }

  Error::Check("initialize");
}

static void display(GLFWwindow *win)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shd->UseProgram();

  int programID = shd->GetID();
  Error::Check("After shd->GetID()");
  glUseProgram(programID); // Use o programa de shader

  int typeLocation = glGetUniformLocation(programID, "objectType");
  if (typeLocation == -1)
  {
    std::cout << "objectType não encontrado";
  }

  glUniform1i(typeLocation, 1); // Define 'objectType' como 1 para disco(s)
  dsk->Draw();

  glUniform1i(typeLocation, 0); // Define 'objectType' como 0 para polígono
  pol->Draw();

  Error::Check("display");
}

static void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void resize(GLFWwindow *win, int width, int height)
{
  glViewport(0, 0, width, height);
}

static void error(int code, const char *msg)
{
  printf("GLFW error %d: %s\n", code, msg);
  glfwTerminate();
  exit(0);
}

int main()
{
  glfwSetErrorCallback(error);
  if (glfwInit() != GLFW_TRUE)
  {
    std::cerr << "Could not initialize GLFW" << std::endl;
    return 0;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // required for mac os

  GLFWwindow *win = glfwCreateWindow(600, 400, "Polygon", nullptr, nullptr);
  if (!win)
  {
    std::cerr << "Could not create GLFW window" << std::endl;
    return 0;
  }
  glfwMakeContextCurrent(win);

#ifdef __glad_h_
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    printf("Failed to initialize GLAD OpenGL context\n");
    exit(1);
  }
#endif

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

  glfwSetFramebufferSizeCallback(win, resize); // resize callback
  glfwSetKeyCallback(win, keyboard);           // keyboard callback

  initialize();
  while (!glfwWindowShouldClose(win))
  {
    display(win);
    glfwSwapBuffers(win);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
