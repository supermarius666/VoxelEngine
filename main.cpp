#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"shaderClass.h"
#include"Texture.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


//vertici di un triangolo equilatero
GLfloat vertices[] = {  
	//vertici		      //colori                       //texture coords
	-0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,	 0.0f,		0.0f,	0.0f,	//punto in basso a sinistra
	-0.5f,	 0.5f,	0.0f,	0.0f,	1.0f,	 0.0f,		0.0f,	1.0f,	//punto in basso a destra
	 0.5f,   0.5f,	0.0f,	0.0f,	0.0f,	 1.0f,		1.0f,	1.0f,	//punto in alto
	 0.5f,  -0.5f,	0.0f,	1.0f,	1.0f,	 1.0f,		1.0f,	0.0f,	//interno a sinistra
};

//indici della forma
GLuint indices[] = {
	0, 2, 1,
	0, 3, 2,
};




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

	//specifico il viewport di OpenGL nella finestra, cioè da dove fino a dove posso vedere
	//in questo caso ho messo da (0,0) a (800,800) quindi tutta la finestra
	glViewport(0, 0, 800, 800);

	
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

	//definisco la variabile uniform scale
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//texture
	Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	//main loop
	while (!glfwWindowShouldClose(window)) {
		
		//colore del back buffer
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//assegno effettivamente il colore al back buffer
		glClear(GL_COLOR_BUFFER_BIT);
		//attivo il program degli shaders
		shaderProgram.Activate();

		//setto il valore della variabile uniform scale
		glUniform1f(uniID, 0.5f);
		popCat.Bind();

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
	//distrugge la texture
	popCat.Delete();

	//distrugge la finestra
	glfwDestroyWindow(window);
	//termina tutto!
	glfwTerminate();
	return 0;
}