#ifndef CUBE_H
#define CUBE_H

#include "shape.h"

class Cube: public Shape {
  public:
    Cube();
    Cube(glm::vec3 color);
};

#endif
