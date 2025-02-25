#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <string>

typedef unsigned Shader;

int shaderConstruct(Shader *shader, const char *vsPath, const char *fsPath);
void shaderUse(Shader shader);
void shaderSetInt(Shader shader, const char *uniform, int value);
void shaderSetFloat(Shader shader, const char *uniform, float value);
void shaderSetVector3f(Shader shader, const char *uniform, glm::vec3 value);
void shaderSetMatrix4(Shader shader, const char *uniform, glm::mat4 value);

#endif
