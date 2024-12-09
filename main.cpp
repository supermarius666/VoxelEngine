#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


//vertici di un triangolo equilatero
GLfloat vertices[] = {
	//vertici				                            //colori
	-0.5f,  -0.5f * float(sqrt(3)) / 3,		0.0f,	0.8f, 0.3f, 0.02f, //punto in basso a sinistra
	0.5f,   -0.5f * float(sqrt(3)) / 3,		0.0f,	0.8f, 0.3f, 0.02f,//punto in basso a destra
	0.0f,    0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	1.0f, 0.6f, 0.32f,//punto in alto
	-0.25f,  0.5f * float(sqrt(3)) / 6,		0.0f,	0.9f, 0.45f, 0.17f,//interno a sinistra
	0.25f,   0.5f * float(sqrt(3)) / 6,		0.0f,	0.9f, 0.45f, 0.17f,//interno a destra
	0.0f,   -0.5f * float(sqrt(3)) / 3,		0.0f,	0.8f, 0.3f, 0.02f,//iterno in basso

};

//indici della forma
GLuint indices[] = {
	0, 3, 5,
	3, 2, 4,
	5, 4, 1
};




int main(void) {

	//init di glfw
	glfwInit();

	//specifica che versione di opengl usare e core_profile
	//utilizzo opengl versione 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//core_profile ha le funzionalit� pi� moderne di opengl
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	

	//Creazione finestra 800x800
	GLFWwindow* window = glfwCreateWindow(800, 800, "Voxel Engine", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create Window!" << std::endl;
		glfwTerminate();
		return (-1);
	} 

	//dire a glfw che voglio usare la finestra che ho creato come curret context
	glfwMakeContextCurrent(window);

	//uso glad per la configurazione di opengl
	gladLoadGL();

	//specifico il viewport di OpenGL nella finestra, cio� da dove fino a dove posso vedere
	//in questo caso ho messo da (0,0) a (800,800) quindi tutta la finestra
	glViewport(0, 0, 800, 800);

	
	//shaders????
	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	//generate vertex
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	
	//main loop
	while (!glfwWindowShouldClose(window)) {
		
		//colore del back buffer
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//assegno effettivamente il colore al back buffer
		glClear(GL_COLOR_BUFFER_BIT);
		//attivo il program degli shaders
		shaderProgram.Activate();
		//bind VAO
		VAO1.Bind();
		//disegno
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		//swap buffers in modo che l'imm agine venga aggiornata
		glfwSwapBuffers(window);
		//aspetta per i vari eventi e risponde
		glfwPollEvents();

	}

	
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	//distrugge la finestra
	glfwDestroyWindow(window);
	//termina tutto!
	glfwTerminate();
	return 0;
}