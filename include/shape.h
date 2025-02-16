#ifndef SHAPE_H
#define SHAPE_H

#include "shader.h"

#define PI glm::pi<float>()

typedef enum { VERTICES, TEXTURE, NORMALS } VBOAttribs;

class Shape {
  protected:
    // OpenGL Data
    unsigned VAO;
    unsigned EBO;
    unsigned VBO[3];
    Shader *shader;

    // Vertex Data
    long numVertices;
    long numTextureCoords;
    long numNormals;
    long numIndices;

    float *vertices;
    float *textureCoordinates;
    float *normals;
    unsigned *indices;

    // Functions
    void setData();

  public:
    ~Shape();
    glm::vec3 color;
    void draw(glm::mat4 model);
};

#endif
