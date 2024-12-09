#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>	
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"shaderClass.h"
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

	//definisco la variabile uniform scale
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//texture
	Texture popCat("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	//depth testing
	glEnable(GL_DEPTH_TEST);

	//main loop
	while (!glfwWindowShouldClose(window)) {
		
		//colore del back buffer
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//assegno effettivamente il colore al back buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//attivo il program degli shaders
		shaderProgram.Activate();


		//inizializzo la matrice model
		glm::mat4 model1 = glm::mat4(1.0f);
		//inizializzo la matrice view
		glm::mat4 view1 = glm::mat4(1.0f);
		//inizializzo la matrice projection
		glm::mat4 projection1 = glm::mat4(1.0f);

		//rotazione
		model1 = glm::rotate(model1, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));


		//setto la posizione della camera
		view1 = glm::translate(view1, glm::vec3(0.0f, -0.5f, -2.0f));
		//setto la proiezione
		projection1 = glm::perspective(glm::radians(45.0f),float(WIDTH / HEIGHT), 0.1f, 100.0f);


		//setto la variabile uniform model
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));

		//setto la variabile uniform view
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view1));

		//setto la variabile uniform projection
		int projectionLoc = glGetUniformLocation(shaderProgram.ID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection1));


		//setto il valore della variabile uniform scale
		glUniform1f(uniID, 0.5f);
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