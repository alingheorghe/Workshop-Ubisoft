#version 400 // 150 daca nu e suportat opengl 4.x dar e suportat 3.3
out vec4 frag_colour;

uniform vec4 color;

void main () {
  frag_colour = color;
}