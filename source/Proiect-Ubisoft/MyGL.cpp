#include "MyGL.h"


void MyGL::initGL(){
	// init glfw
	if (!glfwInit ()) {
		fprintf (stderr, "ERROR: could not start GLFW3\n");
		return ;
	} 

	// Se creeaza fereastra
	window = glfwCreateWindow (640, 480, "Space", NULL, NULL);
	if (!window) {
		// nu am reusit sa facem fereastra, oprim totul si dam mesaj de eroare
		printf ( "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return ;
	}
	// Atasam contextul de fereastra
	glfwMakeContextCurrent (window);
                                  
	// initglew
	glewExperimental = true;
	if(glewInit () != GLEW_OK){
		fprintf(stderr, "ERROR: GLEW faild to initialise");
		glfwTerminate();
		return;
	}
	//load shaders
	loadShaders();

	positionLocation = glGetAttribLocation(shader_programme, "pisition");
	colorLoc = glGetUniformLocation(shader_programme, "color");
}


void MyGL::drawGL(){
	for(int i = 0 ; i < objs.size() ; i ++){
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
		glBindVertexArray(NULL);
		glUniform4f(colorLoc, 0.0, 0.0, 1.0, 1.0);
		glBindVertexArray(objs[i].vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objs[i].ibo);
		glDrawElements(GL_TRIANGLES, objs[i].vertexNumber, GL_UNSIGNED_SHORT, NULL);
		
	}
}

void MyGL::runGL(){
	generateTriangle();
	generatenThagone(5);
	while(!glfwWindowShouldClose(window)){
		
		//screen size
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glViewport( 0, 0, windowWidth, windowHeight);

		// stergem ce s-a desenat anterior
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// spunem ce shader vom folosi pentru desenare
		
		drawGL();
		//events
		glfwPollEvents();
		
		glfwSwapBuffers(window);
	  
	}
}

char * MyGL::LoadFileInMemory(const char* filename){

	int size = 0;
	char *buffer = NULL;
	FILE *f = fopen(filename, "rb");
	if (f == NULL)
	{
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	buffer = new char[size + 1];
	if (size != fread(buffer, sizeof(char), size, f))
	{
		delete[] buffer;
	}
	fclose(f);
	buffer[size] = 0;
	return buffer;

}

void MyGL::loadShaders(){
	
	const char * vertex_shader = LoadFileInMemory("../data/vertexShader.glsl");
	const char * fragment_shader = LoadFileInMemory("../data/fragmentShader.glsl");

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);

	glBindFragDataLocation(shader_programme, 0, "frag_colour");

	glLinkProgram(shader_programme);
	delete[] vertex_shader;
	delete[] fragment_shader;

	glUseProgram(shader_programme);
}

//generare forme;

void MyGL::generateTriangle(){

	GLfloat vertex_buffer[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
	};
	//vertex buffer obj
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_STATIC_DRAW);

	//index buffer obj
	GLuint iboID;
	glGenBuffers(1, &iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);

	GLushort indexData[] = {
		0, 1, 2,
	};

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	//vertex array obj
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	//--------
	

	glEnableVertexAttribArray(positionLocation);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	
	//glUniform4f(colorLoc, 1.0, (rand() % 255)/ 255.0 ,(rand() % 255)/ 255.0 ,1.0);

	objIdent o;
	o.ibo = iboID;
	o.vao = vaoID;
	o.vbo = vboID;
	o.vertexNumber = 3;
	objs.push_back(o);

	vao.push_back(vaoID);
	vbo.push_back(vboID);
	ibo.push_back(iboID);
	vertexNumber.push_back(3);
}

void MyGL::generateSquare(){

	GLfloat vertex_buffer[] = {
		0.5f, 0.5f, 0.0f,//0
		0.5f, -0.5f, 0.0f,//1
		-0.5f, -0.5f, 0.0f,//2
		-0.5f, 0.5f, 0.0f,//3
	};

	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	GLuint iboID;
	glGenBuffers(1, &iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);

	GLushort indexData[] = {
		0, 1, 2,
		0, 2, 3
	};

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);

	
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);


	glEnableVertexAttribArray(positionLocation);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);

	objIdent o;
	o.ibo = iboID;
	o.vao = vaoID;
	o.vbo = vboID;
	o.vertexNumber = 6;
	objs.push_back(o);
	std::cout << o.ibo << " " << iboID << std::endl;
	std::cout << o.vao << " " << vaoID << std::endl;
	std::cout << o.vbo << " " << vboID << std::endl;
	std::cout << o.vertexNumber<< " " << std::endl;

	vao.push_back(vaoID);
	vbo.push_back(vboID);
	ibo.push_back(iboID);
	vertexNumber.push_back(6);
}

void MyGL::generatenThagone(int n){
	GLfloat *vertex_buffer;
	int vertex_size = ((n + 1) * 3 * sizeof(GLfloat));
	vertex_buffer = (GLfloat *)malloc(vertex_size);
	vertex_buffer[0] = vertex_buffer[1] = vertex_buffer[2] = 0.0f;
	std::cout << vertex_buffer[0] << " " << vertex_buffer[1] << " " << vertex_buffer[ 2] << " -- "  << std::endl;
	//generate vertex coord;
	float alpha = 0;
	float r = 0.75;
	float theta = 2 * 3.1415926 / float(n); 
	for(int i = 3 ; i <= n * 3; i += 3){
		vertex_buffer[i] = r*cosf(alpha);
		vertex_buffer[i+1] = r*sinf(alpha);
		vertex_buffer[i+2] = 0.0f;
		
		std::cout << vertex_buffer[i] << " " << vertex_buffer[i+1] << " " << vertex_buffer[i+2] << " -- " << alpha << std::endl;
		alpha += theta;
	}
	
	//vertex buffer obj
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, vertex_size, vertex_buffer, GL_STATIC_DRAW);

	//index buffer obj
	GLuint iboID;
	glGenBuffers(1, &iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);

	GLushort *indexData;
	indexData = (GLushort *) malloc((n + 1) * 3 * sizeof(GLushort));
	short int k = 1;
	for(int i = 0 ; i < n * 3; i += 3){
		indexData[i] = 0;
		indexData[i+1] = k;
		if(k == n)
			indexData[i+2] = 1;
		else
			indexData[i+2] = (++k);
		std::cout << indexData[i] << " " << indexData[i+1] << " " << indexData[i+2] << std::endl;
	}

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);

	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	glEnableVertexAttribArray(positionLocation);
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);


	objIdent o;
	o.ibo = iboID;
	o.vao = vaoID;
	o.vbo = vboID;
	o.vertexNumber = 3 * (n + 1);
	objs.push_back(o);
	
}