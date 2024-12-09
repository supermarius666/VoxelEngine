#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>	
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"shaderClass.h"
#include"camera.h"
#include"Texture.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


//vertici di un triangolo equilatero
GLfloat vertices[] = {  
	//vertici		      //colori                       //texture coords
	-0.5f,	 0.0f,	0.5f,	0.83f,	0.70f,	 0.44f,		0.0f,	0.0f,	
	-0.5f,	 0.0f, -0.5f,	0.83f,	0.70f,	 0.44f,		5.0f,	0.0f,	
	 0.5f,   0.0f, -0.5f,	0.83f,	0.70f,	 0.44f,		0.0f,	0.0f,	
	 0.5f,   0.0f,	0.5f,	0.83f,	0.70f,	 0.44f,		5.0f,	0.0f,	
	 0.0f,   0.8f,	0.0f,	0.92f,	0.86f,	 0.76f,		2.5f,	5.0f,	
};

//indici della forma
GLuint indices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4

};

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;


int main(void) {

	//init di glfw
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW!" << std::endl;
		return -1;
	}

	//specifica che versione di opengl usare e core_profile
	//utilizzo opengl versione 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//core_profile ha le funzionalità più moderne di opengl
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	

	//Creazione finestra 800x800
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Voxel Engine", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create Window!" << std::endl;
		glfwTerminate();
		return (-1);
	} 

	//dire a glfw che voglio usare la finestra che ho creato come curret context
	glfwMakeContextCurrent(window);

	//uso glad per la configurazione di opengl
	gladLoadGL();

	//specifico il viewport di OpenGL nella finestra, cioè da dove fino a dove posso vedere
	//in questo caso ho messo da (0,0) a (800,800) quindi tutta la finestra
	glViewport(0, 0, WIDTH, HEIGHT);

	
	//shaders????
	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	//generate vertex
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//texture
	Texture popCat("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	//depth testing
	glEnable(GL_DEPTH_TEST);


	//camera
	Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

	// Tempo tra il frame corrente e il frame precedente
	float deltaTime = 0.0f;
	// Tempo del frame precedente
	float lastTime = 0.0f;

	//main loop
	while (!glfwWindowShouldClose(window)) {
		
		// Calcola il tempo corrente
		float currentTime = glfwGetTime();
		// Calcola deltaTime
		deltaTime = currentTime - lastTime;
		// Aggiorna lastTime per il prossimo frame
		lastTime = currentTime;


		//colore del back buffer
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//assegno effettivamente il colore al back buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//attivo il program degli shaders
		shaderProgram.Activate();

		
		//input
		camera.Input(window, deltaTime);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
		
		popCat.Bind();

		//bind VAO
		VAO1.Bind();
		//disegno
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		//swap buffers in modo che l'imm agine venga aggiornata
		glfwSwapBuffers(window);
		//aspetta per i vari eventi e risponde
		glfwPollEvents();

	}

	
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	//distrugge la texture
	popCat.Delete();

	//distrugge la finestra
	glfwDestroyWindow(window);
	//termina tutto!
	glfwTerminate();
	return 0;
}