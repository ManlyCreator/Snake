#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>
#include <sstream>
#include "shader.h"

void readFile(std::ifstream *file, std::string *dest);
int shaderCompilationSuccess(unsigned shader);
int programLinkSuccess(unsigned program);

int shaderConstruct(Shader *shader, const std::string vsPath, const std::string fsPath) {
  unsigned vertexShader, fragmentShader;
  std::string vsSource, fsSource;
  std::ifstream vsFile, fsFile; 
  std::stringstream vsStream, fsStream;

  vsFile.open(vsPath);
  fsFile.open(fsPath);

  // Vertex Shader Compilation
  if (!vsFile.is_open()) {
    std::perror("Could not open Vertex Shader\n");
    return 0;
  }
  if (!fsFile.is_open()) {
    std::perror("Could not open Fragment Shader\n");
    return 0;
  }

  readFile(&vsFile, &vsSource);
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, (const char **)&vsSource, NULL);
  glCompileShader(vertexShader);
  if (!shaderCompilationSuccess(vertexShader)) {
    printf("Failed to compile Vertex Shader\n");
    return 0;
  }

  // Fragment Shader Compilation
  readFile(&fsFile, &fsSource);
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, (const char **)&fsSource, NULL);
  glCompileShader(fragmentShader);
  if (!shaderCompilationSuccess(fragmentShader)) {
    printf("Failed to compile Fragment Shader\n");
    return 0;
  }

  // Program Linking
  *shader = glCreateProgram();
  glAttachShader(*shader, vertexShader);
  glAttachShader(*shader, fragmentShader);
  glLinkProgram(*shader);
  if (!programLinkSuccess(*shader))
    return 0;

  // Free Memory
  fclose(vsFile);
  fclose(fsFile);

  return 1;
}

void shaderUse(Shader shader) {
  glUseProgram(shader);
}

void shaderSetFloat(Shader shader, const char *uniform, float value) {
  glUniform1f(glGetUniformLocation(shader, uniform), value);
}

void shaderSetInt(Shader shader, const char *uniform, int value) {
  glUniform1i(glGetUniformLocation(shader, uniform), value);
}

void shaderSetVector3f(Shader shader, const char *uniform, vec3 value) {
  glUniform3f(glGetUniformLocation(shader, uniform), value[0], value[1], value[2]);
}

void shaderSetMatrix4(Shader shader, const char *uniform, mat4 value) {
  glUniformMatrix4fv(glGetUniformLocation(shader, uniform), 1, GL_FALSE, (float *)value);
}

void readFile(std::ifstream *file, std::string *dest) {

}

int shaderCompilationSuccess(unsigned shader) {
  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    printf("*** ERROR COMPILING SHADER ***\n%s\n", infoLog);
    return 0;
  }
  return 1;
}

int programLinkSuccess(unsigned program) {
  int success;
  char infoLog[512];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    printf("*** ERROR LINKING PROGRAM ***\n%s", infoLog);
    return 0;
  }
  return 1;
}
