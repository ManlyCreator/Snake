#ifndef TORUS_H
#define TORUS_H

#include "shape.h"

class Torus: public Shape {
  public:
    Torus();
    Torus(int rings, int stacks, float insideRadius, float ringRadius, glm::vec3 objColor);
};

#endif
