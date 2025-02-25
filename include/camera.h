#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#define CAMERA_SPEED 0.5f
#define CAMERA_SENSITIVITY 0.01f
#define WORLD_UP (glm::vec3){0.0f, 1.0f, 0.0f}

typedef enum { FORWARD, BACKWARD, RIGHT, LEFT } CameraDirection;

typedef struct {
  float pitch;
  float yaw;
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 right;
  glm::vec3 up;
  glm::mat4 view;
} Camera;

Camera cameraInit(glm::vec3 position, float pitch, float yaw);
void cameraProcessKeyboard(Camera *camera, CameraDirection direction);
void cameraProcessMouse(Camera *camera, float deltaX, float deltaY);
void cameraUpdateView(Camera *camera);

#endif // !CAMERA_H
