#include "torus.h"
#include "shape.h"
#include <glm/ext/scalar_constants.hpp>
#include <iostream>

Torus::Torus() {
  shader = nullptr;
  vertices = nullptr;
  textureCoordinates = nullptr;
  normals = nullptr;
  indices = nullptr;
}

Torus::Torus(int rings, int stacks, float insideRadius, float ringRadius, glm::vec3 objColor) : Shape() {
  float x, y, z;
  float xz;
  float nx, ny, nz;
  float radiusInv = 1.0f / ringRadius;
  float s, t;
  float insideAngle, ringAngle;
  float v1, v2;
  float insideAngleStep = 2 * PI / rings;
  float ringAngleStep = 2 * PI / stacks;

  numVertices = 0;
  numTextureCoords = 0;
  numNormals = 0;
  numIndices = 0;

  shader = nullptr;
  color = objColor;
  vertices = new float[(rings + 1) * (stacks + 1) * 3 * sizeof(float)];
  textureCoordinates = new float[(rings + 1) * (stacks + 1) * 2 * sizeof(float)];
  normals = new float[(rings + 1) * (stacks + 1) * 3 * sizeof(float)];
  indices = new unsigned[rings * stacks * 6 * sizeof(unsigned)];

  for (int i = 0; i <= rings; i++) {
    insideAngle = i * insideAngleStep;

    for (int j = 0; j <= stacks; j++) {
      ringAngle = PI - j * ringAngleStep;

      // Normals
      xz = ringRadius * cos(ringAngle);
      x = xz * cos(insideAngle);
      y = sin(ringAngle);
      z = xz * sin(insideAngle);

      nx = x * radiusInv; 
      ny = y * radiusInv; 
      nz = z * radiusInv; 

      normals[numNormals++] = nx; 
      normals[numNormals++] = ny; 
      normals[numNormals++] = nz; 

      // Vertices
      x += insideRadius * cos(insideAngle);
      z += insideRadius * sin(insideAngle);

      vertices[numVertices++] = x;
      vertices[numVertices++] = y;
      vertices[numVertices++] = z;

      // Texture Coordinates
      s = (float)i * 2.0f / rings;
      t = (float)j / stacks;
      textureCoordinates[numTextureCoords++] = s;
      textureCoordinates[numTextureCoords++] = t;
    }
  }

  for (int i = 0; i < rings; i++) {
    v1 = i * (stacks + 1); 
    v2 = v1 + stacks + 1;
    for (int j = 0; j < stacks; j++, v1++, v2++) {
      indices[numIndices++] = v1;
      indices[numIndices++] = v2;
      indices[numIndices++] = v1 + 1;

      indices[numIndices++] = v1 + 1;
      indices[numIndices++] = v2;
      indices[numIndices++] = v2 + 1;
    }
  }
}
