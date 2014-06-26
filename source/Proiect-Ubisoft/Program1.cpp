#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <iostream>

// functie banala de incarcat continutul unui fisier intr-un buffer
char * LoadFileInMemory(const char *filename)
{
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


int main () {
  // Initializare (se creeaza contextul)
  if (!glfwInit ()) {
    fprintf (stderr, "ERROR: could not start GLFW3\n");
    return 1;
  } 

  // Se creeaza fereastra
  GLFWwindow* window = glfwCreateWindow (640, 480, "Workshop1", NULL, NULL);
  if (!window) {
    // nu am reusit sa facem fereastra, oprim totul si dam mesaj de eroare
	printf ( "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  // Atasam contextul de fereastra
  glfwMakeContextCurrent (window);
                                  
  // Pornit extension handler-ul
  glewInit ();

  // Vedem versiunile
  const GLubyte* renderer = glGetString (GL_RENDERER); //renderer string
  const GLubyte* version = glGetString (GL_VERSION); // version string
  printf ("Renderer: %s\n", renderer);
  printf ("OpenGL version supported %s\n", version);

  const char * vertex_shader = LoadFileInMemory("../data/vertexShader.glsl");
  const char * fragment_shader = LoadFileInMemory("../data/fragmentShader.glsl");
  printf("%s \n", vertex_shader);
  printf("%s \n", fragment_shader);
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);
  GLuint shader_programme = glCreateProgram();
  glAttachShader(shader_programme, fs);
  glAttachShader(shader_programme, vs);
  glLinkProgram(shader_programme);

  delete[] vertex_shader;
  delete[] fragment_shader;

  // buffer cu vertecsi in RAM 
  float t_vertex_buffer[] = {
	  0.0f, 0.5f, 0.0f,
	  0.5f, 0.5f, 0.0f,
	  0.5f, -0.5f, 0.0f,
	  0.5f, 0.5f, 0.0f,
	  -0.5f, -0.5f, 0.0f,
	  0.5f, 0.5f, 0.0f
  };
  float p_vertex_buffer[] = {
	  0.5f, 0.5f, 0.0f,
	  0.5f, -0.5f, 0.0f,
	  -0.5f, -0.5f, 0.0f,

	  -0.5f, -0.5f, 0.0f,
	  -0.5f, 0.5f, 0.0f,
	  0.5f, 0.5f, 0.0f
  };
  //---Alegem tipul desenului---
  printf("Va rugam sa alegeti tipul desenului :\n");
  printf("1.Triunghi\n");
  printf("2.Patrat\n");
  printf("3.Cerc\n");
  char aleg = getchar();
  int n = 0;
  float *vertex_buffer;
  if(aleg == '1'){
	  n = 9;
	  vertex_buffer = t_vertex_buffer;
  }else{
	if(aleg == '2'){
		n = 18;
		vertex_buffer = p_vertex_buffer;
	}else{
		printf("Introduceti numarul de vertexi:\n");
		std::cin >> n;
		float alpha = 0;
		float r = 0.5;
		float *points;

		float theta = 2 * 3.1415926 / float(n); 
		float c = cosf(theta);//precalculate the sine and cosine
		float s = sinf(theta);
		float x;
		float y; 
		points = (float*)malloc((n+1)*2* sizeof(float));
		
		for(int i = 0 ; i < n*2; i+=2){
			
			x = r*cos(alpha);
			y = r*sin(alpha);
			alpha += theta;
			points[i] = x;
			points[i+1] = y;
			
		}
		points[n*2] = points[0];
		points[n*2 + 1] = points[1];
		int k = 0;
		vertex_buffer = (float *)malloc(n*9*sizeof(float));
		for(int i = 0; i < n*9 ; i+=3){
			vertex_buffer[i] = 0.0f;
			vertex_buffer[i+1] = 0.0f;
			vertex_buffer[i+2] = 0.0f;
			i += 3;
			vertex_buffer[i] = points[k];
			vertex_buffer[i+1] = points[k+1];
			vertex_buffer[i+2] = 0.0f;
			i += 3;
			k += 2;
			vertex_buffer[i] = points[k];
			vertex_buffer[i+1] = points[k+1];
			vertex_buffer[i+2] = 0.0f;
		}
		n *= 9;
		free(points);
	}
  }

  // Generam un buffer in memoria video si scriem in el punctele din ram
  GLuint vbo = 0;
  glGenBuffers(1, &vbo); // generam un buffer 
  glBindBuffer(GL_ARRAY_BUFFER, vbo); // setam bufferul generat ca bufferul curent 
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_STATIC_DRAW); //  scriem in bufferul din memoria video informatia din bufferul din memoria RAM

  // De partea aceasta am uitat sa va spun la curs -> Pentru a defini bufferul alocat de opengl ca fiind buffer de in de atribute, stream de vertecsi trebuie sa :
  // 1. Ii spunem OpenGL-ului ca vom avea un slot pentru acest atribut (in cazul nostru 0) , daca mai aveam vreun atribut ar fi trebuit si acela enablat pe alt slot (de exemplu 1)
  // 2. Definit bufferul ca Vertex Attribute Pointer cu glVertexAttribPointer
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  while (!glfwWindowShouldClose(window)) {
	  //..... Randare................. 
	  // stergem ce s-a desenat anterior
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  // spunem ce shader vom folosi pentru desenare
	  glUseProgram(shader_programme);
	  // facem bind la vertex buffer
	  glBindBuffer(GL_ARRAY_BUFFER, vbo);
	  // draw points 0-3 from the currently bound VAO with current in-use shader
	  glDrawArrays(GL_TRIANGLES, 0, n/3);
	  // facem swap la buffere (Double buffer)
	  glfwSwapBuffers(window);

	  glfwPollEvents();
	}
  
  glfwTerminate();
  return 0;
}