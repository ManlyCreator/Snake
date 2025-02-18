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

  public:
    ~Shape();
    glm::vec3 color;
    // Sets data that has to be loaded after the WebGL context is loaded
    void setData(Shader *newShader);
    // Renders the shape
    void draw(glm::mat4 model);
};

#endif
