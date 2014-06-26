#pragma once

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <vector>
#include <iostream>

class MyGL
{
public:
	GLFWwindow* window;
	GLint windowWidth;
	GLint windowHeight;
	GLuint shader_programme;

	GLint positionLocation;
	GLint colorLoc;

	std::vector<GLuint> vbo;
	std::vector<GLuint> vao;
	std::vector<GLuint> ibo;
	std::vector<int> vertexNumber;

public:
	void initGL();
	void drawGL();
	void runGL();
	char * LoadFileInMemory(const char *filename);
	void loadShaders();
	//generare forme;
	void generateTriangle();
	void generateSquare();
	void generatenThagone(int n);
};

