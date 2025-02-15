#include "cube.h"
#include "shape.h"

Cube cubeInit(vec3 color, Shader *shader) {
  Cube cube;
  float vertices[] = {
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
  float textureCoords[] = {
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
  float normals[] = {
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

  cube.shader = shader;

  cube.numVertices = sizeof(vertices) / sizeof(vertices[0]);
  cube.numTextureCoords = sizeof(textureCoords) / sizeof(textureCoords[0]);
  cube.numNormals = sizeof(normals) / sizeof(normals[0]);
  cube.numIndices = 0;

  cube.vertices = vertices;
  cube.textureCoordinates = textureCoords;
  cube.normals = normals;
  cube.indices = NULL;
  glm_vec3_copy(color, cube.color);

  shapeSetData(&cube);

  return cube;
}
