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

#define WIDTH 1000
#define HEIGHT 1000
#define SPEED 3.0f
#define CUBE_SIZE 2.0f
#define GRID_SIZE 5
#define GRID_SPACING 0.5f

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void cursorPosCallback(GLFWwindow *window, double x, double y);
void processInput(GLFWwindow *window);

int width, height;

double lastX, lastY;
double deltaX, deltaY;
double currentTime;
double timeFactor;

glm::vec3 cameraPos(0.0f, 20.0f, 10.0f);
glm::vec3 snakeColor(0.282f, 0.827f, 1.0f);
glm::mat4 projection(1.0f);

Camera camera(cameraPos);
Cube head = Cube(snakeColor);
Cube grid = Cube(glm::vec3(0.5f, 0.5f, 0.5f));

// TODO: Add spacing between grid cells, possibly by multiplying i & j by GRID_SPACING
// TODO: Change Snake direction with input

int main(void) {
  glm::mat4 view, model;
  GLFWwindow *window;

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
  Shader objectShader("../shaders/objectVertexShader.glsl", "../shaders/objectFragmentShader.glsl");
  camera.attachShader(&objectShader);
  grid.setData(&objectShader);
  head.setData(&objectShader);
  
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
    objectShader.setMatrix4("projection", projection);
    camera.lookAt(camera.getPosition(), glm::vec3(0.0f), WORLD_UP);
    
    // Grid
    for (int i = -GRID_SIZE / 2; i <= GRID_SIZE / 2; i++) {
      float currentX = i * CUBE_SIZE;
      for (int j = -GRID_SIZE / 2; j <= GRID_SIZE / 2; j++) {
        std::cout << "i = " << i << "\n";
        std::cout << "j = " << j << "\n";
        float currentZ = j * CUBE_SIZE;
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(currentX, 0.0f, currentZ));
        model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.0f));
        grid.draw(model);
        std::cout << "currentX = " << currentX << "\n";
        std::cout << "currentZ = " << currentZ << "\n";
      }
    }

    // Snake
    model = glm::mat4(1.0f);
    /*model = glm::translate(model, glm::vec3(0.0f, 0.0f, -currentTime * SPEED));*/
    model = glm::translate(model, glm::vec3(0.0f, CUBE_SIZE, 0.0f));
    head.draw(model);

    // Poll Events & Swap Buffers
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  // Clean-Up
  head.free();
  camera.free();
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

  camera.processMouse(deltaX, deltaY);

  lastX = x;
  lastY = y;
}

void processInput(GLFWwindow *window) {
  // Exit
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  // Camera Controls
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.processKeyboard(FORWARD);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.processKeyboard(BACKWARD);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.processKeyboard(RIGHT);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.processKeyboard(LEFT);
}
