#version 400 // 150 daca nu e suportat opengl 4.x dar e suportat 3.3
in leyout(location = 0) vec3 vp;
in layout(location = 1) vec3 vertexColor;
out vec3 sendColor;
void main () {
  gl_Position = vec4 (vp, 1.0);
  sendColor = vertexColor;
}