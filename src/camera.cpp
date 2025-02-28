#include "camera.h"
#include <iostream>
#include <glad/glad.h>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(glm::vec3 position) {
  this->position = position;
  updateVectors(); 
}

Camera::Camera(glm::vec3 position, float pitch, float yaw) {
  this->position = position;

  updateVectors(); 

  this->pitch = pitch;
  this->yaw = yaw;
}

void Camera::attachShader(Shader *shader) {
  this->shader = shader;
}

void Camera::processKeyboard(CameraDirection direction) {
  glm::vec3 dir;
  if (direction == FORWARD) {
    dir = front * CAMERA_SPEED;
    position += dir;
  }
  if (direction == BACKWARD) {
    dir = front * CAMERA_SPEED;
    position -= dir;
  }
  if (direction == RIGHT) {
    dir = glm::normalize(glm::cross(front, WORLD_UP)) * CAMERA_SPEED;
    position += dir;
  }
  if (direction == LEFT) {
    dir = glm::normalize(glm::cross(front, WORLD_UP)) * CAMERA_SPEED;
    position -= dir;
  }
}

void Camera::processMouse(float deltaX, float deltaY) {
  pitch = glm::clamp(pitch + (deltaY * CAMERA_SENSITIVITY), glm::radians(-89.9f), glm::radians(89.9f));
  yaw += deltaX * CAMERA_SENSITIVITY;
  updateVectors();
}

void Camera::updateView() {
  glm::vec3 lookDir;
  glm::mat4 lookAt(1.0f);

  front.x = cos(yaw) * cos(pitch);
  front.y = sin(pitch);
  front.z = sin(yaw) * cos(pitch);

  lookDir = position + front;
  this->lookAt(position, lookDir, WORLD_UP);
}

void Camera::lookAt(glm::vec3 position, glm::vec3 lookPos, glm::vec3 up) {
  view = glm::lookAt(position, lookPos, up);
  shader->setMatrix4("view", view);
}

void Camera::free() {
  if (shader) {
    glDeleteProgram(shader->getID());
  }
}

void Camera::updateVectors() {
  // Calculate Right Vector
  right = glm::normalize(glm::cross(front, WORLD_UP));

  // Calculate Up Vector
  up = glm::normalize(glm::cross(right, front));
}
