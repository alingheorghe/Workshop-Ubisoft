#version 400 // 150 daca nu e suportat opengl 4.x dar e suportat 3.3
out vec4 frag_colour;
in vec3 color_vector;
void main () {
  frag_colour = vec4 (color_vector, 1.0);
}