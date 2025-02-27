// Standard C++ Libraries
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>

// OpenGL Libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// External Libraries
#include "camera.h"
#include "shader.h"
#include "cube.h"
#include "torus.h"

#define WIDTH 1000
#define HEIGHT 1000
#define SPEED 3.0f

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void cursorPosCallback(GLFWwindow *window, double x, double y);
void processInput(GLFWwindow *window);

double currentTime;
glm::mat4 projection(1.0f);

double lastX, lastY;
double deltaX, deltaY;

Camera camera;
glm::vec3 snakeColor(0.282f, 0.827f, 1.0f);
Cube head = Cube(snakeColor);
int width, height;
double timeFactor;

// TODO: Init camera using only Camera functions
// TODO: Update Camera to C++ paradigm
// TODO: Change Snake direction with input

int main(void) {
  Shader objectShader;
  glm::mat4 view, model;
  GLFWwindow *window;
  glm::vec3 lightPos = {5.0f, 10.0f, 0.0f};
  glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

  // GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(WIDTH, HEIGHT, PROJECT, NULL, NULL);

  if (window == NULL) {
    std::cerr << "Window creation failed\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to load GLAD\n";
    glfwTerminate();
    return -1;
  }

  glViewport(0, 0, WIDTH, HEIGHT);

  // Shaders
  if (!shaderConstruct(&objectShader, "../shaders/objectVertexShader.glsl", "../shaders/objectFragmentShader.glsl"))
    return -1;
  head.setData(&objectShader);
  
  // Camera
  camera = cameraInit(glm::vec3(0.0f, 20.0f, 5.0f), 0.0f, 0.0f);

  // Transformations
  projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 200.0f);

  // Callbacks
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  // Sets lastX & lastY to center of screen for proper delta calculation
  glfwGetWindowSize(window, &width, &height);
  lastX = (float)width / 2;
  lastY = (float)height / 2;
  glfwSetCursorPosCallback(window, cursorPosCallback);

  // Render Loop
  while (!glfwWindowShouldClose(window)) {
    currentTime = glfwGetTime();

    // Input
    processInput(window);

    // Render Commands
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDisable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Object Shader
    shaderUse(objectShader);
    shaderSetMatrix4(objectShader, "projection", projection);
    /*camera.view = glm::mat4(1.0f);*/
    /*camera.view = glm::lookAt(glm::vec3(0.0f, 10.0f, 10.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/
    cameraUpdateView(&camera);
    shaderSetMatrix4(objectShader, "view", camera.view);
    shaderSetVector3f(objectShader, "lightColor", lightColor);
    shaderSetVector3f(objectShader, "lightPos", lightPos);
    
    // Draw Objects
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -currentTime * SPEED));
    head.draw(model);

    // Poll Events & Swap Buffers
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  // Clean-Up
  glfwTerminate();

  return 0;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
  projection = glm::mat4(1.0f);
  projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 200.0f);
}

void cursorPosCallback(GLFWwindow *window, double x, double y) {
  deltaX = x - lastX;
  deltaY = (y - lastY) * -1;

  cameraProcessMouse(&camera, deltaX, deltaY);

  lastX = x;
  lastY = y;
}

void processInput(GLFWwindow *window) {
  // Exit
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  // Camera Controls
  /*if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)*/
  /*  cameraProcessKeyboard(&camera, FORWARD);*/
  /*if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)*/
  /*  cameraProcessKeyboard(&camera, BACKWARD);*/
  /*if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)*/
  /*  cameraProcessKeyboard(&camera, RIGHT);*/
  /*if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)*/
  /*  cameraProcessKeyboard(&camera, LEFT);*/
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    cameraProcessKeyboard(&camera, FORWARD);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    cameraProcessKeyboard(&camera, BACKWARD);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    cameraProcessKeyboard(&camera, RIGHT);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    cameraProcessKeyboard(&camera, LEFT);
}
