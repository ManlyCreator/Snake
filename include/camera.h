#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include "shader.h"

#define CAMERA_SPEED 0.5f
#define CAMERA_SENSITIVITY 0.01f
#define WORLD_UP (glm::vec3){0.0f, 1.0f, 0.0f}

typedef enum { FORWARD, BACKWARD, RIGHT, LEFT } CameraDirection;

class Camera {
  private:
    Shader *shader;
    float pitch;
    float yaw;
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    void updateVectors();

  public:
    glm::mat4 view;

    Camera(glm::vec3 position);
    Camera(glm::vec3 position, float pitch, float yaw);

    void attachShader(Shader *shader);
    void processKeyboard(CameraDirection direction);
    void processMouse(float deltaX, float deltaY);
    void updateView();
    void lookAt(glm::vec3 position, glm::vec3 lookPos, glm::vec3 up);
    void free();
    glm::vec3 getPosition() { return position; };
};

#endif // !CAMERA_H
