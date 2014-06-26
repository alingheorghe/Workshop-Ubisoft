#version 400 // 150 daca nu e suportat opengl 4.x dar e suportat 3.3
in layout(location = 0) vec3 vp;
out vec3 sendColor;
void main () {
  gl_Position = vec4 (vp, 1.0);
}