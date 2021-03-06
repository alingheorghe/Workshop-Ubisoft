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
	int flip;
	typedef struct objIdent{
		GLuint vao;
		GLuint vbo;
		GLuint ibo;
		int vertexNumber;
	};

	std::vector<objIdent> objs;

public:
	void initGL();
	void drawGL();
	void runGL(int optiune, int n);
	char * LoadFileInMemory(const char *filename);
	void loadShaders();
	//generare forme;
	void generateTriangle();
	void generateSquare();
	void generatenThagone(int n);
};

