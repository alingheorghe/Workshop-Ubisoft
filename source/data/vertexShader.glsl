#version 400 // 150 daca nu e suportat opengl 4.x dar e suportat 3.3
in vec3 pisition;
void main () {
  gl_Position = vec4 (pisition, 1.0);
}