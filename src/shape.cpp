#include "shape.h"
#include "shader.h"
#include <glad/glad.h>
#include <iostream>

void Shape::setData(Shader *newShader) {
  shader = newShader;
  // VAO
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // VBOs
  glGenBuffers(VERTEX_BUFFERS, VBO);

  // Vertices
  glBindBuffer(GL_ARRAY_BUFFER, VBO[VERTICES]);
  glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(float), vertices, GL_STATIC_DRAW);
  
  // Texture
  glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE]);
  glBufferData(GL_ARRAY_BUFFER, numTextureCoords * sizeof(float), textureCoordinates, GL_STATIC_DRAW);

  // Normals
  if (numNormals) {
    glBindBuffer(GL_ARRAY_BUFFER, VBO[NORMALS]);
    glBufferData(GL_ARRAY_BUFFER, numNormals * sizeof(float), normals, GL_STATIC_DRAW);
  }

  // Indices
  EBO = 0;
  if (numIndices) {
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned), indices, GL_STATIC_DRAW);
  }

  // Unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  if (EBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Shape::draw(glm::mat4 model) {
  glBindVertexArray(VAO);

  // Transform
  shaderSetMatrix4(*shader, "model", model);
  shaderSetVector3f(*shader, "objectColor", color);

  // Vertices
  glBindBuffer(GL_ARRAY_BUFFER, VBO[VERTICES]);
  glEnableVertexAttribArray(VERTICES);
  glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  // Texture
  glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE]);
  glEnableVertexAttribArray(TEXTURE);
  glVertexAttribPointer(TEXTURE, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);

  if (numNormals) {
    glBindBuffer(GL_ARRAY_BUFFER, VBO[NORMALS]);
    glEnableVertexAttribArray(NORMALS);
    glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  }

  // Draw
  if (numIndices) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (void*)0);
  } else
    glDrawArrays(GL_TRIANGLES, 0, numVertices / 3);

  // Reset
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  if (EBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Shape::free() {
  glDeleteBuffers(VERTEX_BUFFERS, VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteVertexArrays(1, &VAO);
  if (shader != nullptr)
    glDeleteShader(*shader);
  if (vertices != nullptr)
    delete [] vertices;
  if (textureCoordinates != nullptr)
    delete [] textureCoordinates;
  if (normals != nullptr)
    delete [] normals;
  if (indices != nullptr)
    delete [] indices;
}
