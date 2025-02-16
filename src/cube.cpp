#include "cube.h"
#include "shape.h"

Cube::Cube() {}

Cube::Cube(glm::vec3 color, Shader *shader) : Shape() {
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

  vertices = tempVertices;
  textureCoordinates = tempTextureCoords;
  normals = tempNormals;
  indices = NULL;
  color = color;

  setData();
}
