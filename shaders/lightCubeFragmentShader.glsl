#version 300 es
precision highp float;

uniform vec3 objectColor;

out vec4 fragCol;

void main(void) {
  fragCol = vec4(objectColor, 1.0f);
}
