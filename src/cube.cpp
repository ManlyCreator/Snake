#include "cube.h"
#include "shape.h"
#include <algorithm>
#include <iterator>

Cube::Cube() {
  shader = nullptr;
  vertices = nullptr;
  textureCoordinates = nullptr;
  normals = nullptr;
  indices = nullptr;
}

Cube::Cube(glm::vec3 color, Shader *shader) : Shape() {
  printf("Constructing Cube\n");
  float tempVertices[] = {
    // Front
    -1.0f, -1.0f, 1.0f,  
     1.0f, -1.0f, 1.0f,  
     1.0f,  1.0f, 1.0f,  
    -1.0f, -1.0f, 1.0f,  
     1.0f,  1.0f, 1.0f,  
    -1.0f,  1.0f, 1.0f,  
    
    // Back
    -1.0f, -1.0f, -1.0f, 
     1.0f, -1.0f, -1.0f, 
     1.0f,  1.0f, -1.0f, 
    -1.0f, -1.0f, -1.0f, 
     1.0f,  1.0f, -1.0f, 
    -1.0f,  1.0f, -1.0f, 

    // Right
     1.0f, -1.0f,  1.0f, 
     1.0f, -1.0f, -1.0f, 
     1.0f,  1.0f, -1.0f, 
     1.0f, -1.0f,  1.0f, 
     1.0f,  1.0f, -1.0f, 
     1.0f,  1.0f,  1.0f, 

    // Left
    -1.0f, -1.0f, -1.0f, 
    -1.0f, -1.0f,  1.0f, 
    -1.0f,  1.0f,  1.0f, 
    -1.0f, -1.0f, -1.0f, 
    -1.0f,  1.0f,  1.0f, 
    -1.0f,  1.0f, -1.0f, 

    // Top
    -1.0f,  1.0f,  1.0f, 
     1.0f,  1.0f,  1.0f, 
     1.0f,  1.0f, -1.0f, 
    -1.0f,  1.0f,  1.0f, 
     1.0f,  1.0f, -1.0f, 
    -1.0f,  1.0f, -1.0f, 

    // Bottom
    -1.0f, -1.0f,  1.0f, 
     1.0f, -1.0f,  1.0f, 
     1.0f, -1.0f, -1.0f, 
    -1.0f, -1.0f,  1.0f, 
     1.0f, -1.0f, -1.0f, 
    -1.0f, -1.0f, -1.0f, 
  };
  float tempTextureCoords[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,  
    1.0f, 1.0f,
    0.0f, 0.0f,  
    1.0f, 1.0f,
    0.0f, 1.0f,
               
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
               
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
               
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
               
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
               
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
  };
  float tempNormals[] = {
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f, 
    0.0f,  0.0f, -1.0f, 
    0.0f,  0.0f, -1.0f, 
    0.0f,  0.0f, -1.0f, 
    0.0f,  0.0f, -1.0f, 

    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,

   -1.0f,  0.0f,  0.0f,
   -1.0f,  0.0f,  0.0f,
   -1.0f,  0.0f,  0.0f,
   -1.0f,  0.0f,  0.0f,
   -1.0f,  0.0f,  0.0f,
   -1.0f,  0.0f,  0.0f,

    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,

    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,

    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f
  };

  shader = shader;

  numVertices = sizeof(tempVertices) / sizeof(tempVertices[0]);
  numTextureCoords = sizeof(tempTextureCoords) / sizeof(tempTextureCoords[0]);
  numNormals = sizeof(tempNormals) / sizeof(tempNormals[0]);
  numIndices = 0;

  vertices = new float[numVertices * sizeof(float)];
  textureCoordinates = new float[numTextureCoords * sizeof(float)];
  normals = new float[numNormals * sizeof(float)];
  indices = nullptr;

  std::copy(std::begin(tempVertices), std::end(tempVertices), vertices);
  std::copy(std::begin(tempTextureCoords), std::end(tempTextureCoords), textureCoordinates);
  std::copy(std::begin(tempNormals), std::end(tempNormals), normals);

  color = color;

  setData();
}
