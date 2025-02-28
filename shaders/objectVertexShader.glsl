#version 330 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 objectColor;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 inTexCoords;
layout (location = 2) in vec3 normalPos;

out vec3 outCol;

void main(void) {
  gl_Position = projection * view * model * vec4(pos, 1.0f);
  outCol = objectColor * ((pos.y + 2.0f) * 0.5f);
}
