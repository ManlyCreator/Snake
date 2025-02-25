#include "camera.h"
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>

void updateVectors(Camera *camera);

Camera cameraInit(glm::vec3 position, float pitch, float yaw) {
  Camera camera;

  camera.position = position;
  updateVectors(&camera);
  camera.pitch = pitch;
  camera.yaw = yaw;

  return camera;
}

void cameraProcessKeyboard(Camera *camera, CameraDirection direction) {
  glm::vec3 dir;
  if (direction == FORWARD) {
    dir = camera->front * CAMERA_SPEED;
    camera->position += dir;
  }
  if (direction == BACKWARD) {
    dir = camera->front * CAMERA_SPEED;
    camera->position -= dir;
  }
  if (direction == RIGHT) {
    dir = glm::normalize(glm::cross(camera->front, WORLD_UP)) * CAMERA_SPEED;
    camera->position += dir;
  }
  if (direction == LEFT) {
    dir = glm::normalize(glm::cross(camera->front, WORLD_UP)) * CAMERA_SPEED;
    camera->position -= dir;
  }
}

void cameraProcessMouse(Camera *camera, float deltaX, float deltaY) {
  camera->pitch = glm::clamp(camera->pitch + (deltaY * CAMERA_SENSITIVITY), glm::radians(-89.9f), glm::radians(89.9f));
  camera->yaw += deltaX * CAMERA_SENSITIVITY;
  updateVectors(camera);
}

void cameraUpdateView(Camera *camera) {
  glm::vec3 lookDir;
  glm::mat4 lookAt(1.0f);

  camera->front.x = cos(camera->yaw) * cos(camera->pitch);
  camera->front.y = sin(camera->pitch);
  camera->front.z = sin(camera->yaw) * cos(camera->pitch);

  lookDir = camera->position + camera->front;
  camera->view = glm::lookAt(camera->position, lookDir, WORLD_UP);
}

void updateVectors(Camera *camera) {
  // Calculate Right Vector
  camera->right = glm::normalize(glm::cross(camera->front, WORLD_UP));

  // Calculate Up Vector
  camera->up = glm::normalize(glm::cross(camera->right, camera->front));
}
