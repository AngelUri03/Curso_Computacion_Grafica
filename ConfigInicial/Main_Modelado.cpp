//Práctica 4
//Morales Galicia Angel Uriel
//24-02-2025
//319108745

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica #4 Modelado geometrico Morales Galicia Angel Uriel", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 0.949f, 0.933f,0.621f,//Front
		0.5f, -0.5f, 0.5f,  0.949f, 0.933f,0.621f,
		0.5f,  0.5f, 0.5f,  0.949f, 0.933f,0.621f,
		0.5f,  0.5f, 0.5f,  0.949f, 0.933f,0.621f,
		-0.5f,  0.5f, 0.5f, 0.949f, 0.933f,0.621f,
		-0.5f, -0.5f, 0.5f, 0.949f, 0.933f,0.621f,
		
	    -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,//Back
		 0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	    -0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	    -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		
		 0.5f, -0.5f,  0.5f,  0.496f, 0.121f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.496f, 0.121f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.496f, 0.121f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.496f, 0.121f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.496f, 0.121f, 0.0f,
		 0.5f,  -0.5f, 0.5f,  0.496f, 0.121f, 0.0f,
      
		-0.5f,  0.5f,  0.5f,  1.0f, 0.414f, 0.246f,
		-0.5f,  0.5f, -0.5f,  1.0f, 0.414f, 0.246f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.414f, 0.246f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.414f, 0.246f,
		-0.5f, -0.5f,  0.5f,  1.0f, 0.414f, 0.246f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.414f, 0.246f,
		
		-0.5f, -0.5f, -0.5f, 0.8f, 0.8f,0.8f,
		0.5f, -0.5f, -0.5f,  0.8f, 0.8f,0.8f,
		0.5f, -0.5f,  0.5f,  0.8f, 0.8f,0.8f,
		0.5f, -0.5f,  0.5f,  0.8f, 0.8f,0.8f,
		-0.5f, -0.5f,  0.5f, 0.8f, 0.8f,0.8f,
		-0.5f, -0.5f, -0.5f, 0.8f, 0.8f,0.8f,
		
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.2f,0.5f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	

		glBindVertexArray(VAO);
		GLint colorLoc = glGetUniformLocation(ourShader.Program, "color");

		//Cuerpo

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.9f, 1.2f, 2.0f));

		glUniform3f(colorLoc, 0.949f, 0.933f, 0.621f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.91f, 0.8f, 0.7f));
		model = glm::translate(model, glm::vec3(0.0f, 0.26f, -0.5f));

		glUniform3f(colorLoc, 0.496f, 0.121f, 0.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//Patas

	    model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.8f, 0.2f));
		model = glm::translate(model, glm::vec3(-1.4f, -1.1f, 4.0f));

		glUniform3f(colorLoc, 0.949f, 0.933f, 0.621f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.21f, 0.21f, 0.21f));
		model = glm::translate(model, glm::vec3(-1.35f, -5.6f, 3.8f));

		glUniform3f(colorLoc, 0.496f, 0.121f, 0.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.8f, 0.2f));
		model = glm::translate(model, glm::vec3(-1.4f, -1.1f, -4.0f));

		glUniform3f(colorLoc, 0.949f, 0.933f, 0.621f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.21f, 0.21f, 0.21f));
		model = glm::translate(model, glm::vec3(-1.35f, -5.6f, -3.8f));

		glUniform3f(colorLoc, 0.496f, 0.121f, 0.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.8f, 0.2f));
		model = glm::translate(model, glm::vec3(1.4f, -1.1f, -4.0f));

		glUniform3f(colorLoc, 0.949f, 0.933f, 0.621f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.21f, 0.21f, 0.21f));
		model = glm::translate(model, glm::vec3(1.35f, -5.6f, -3.8f));

		glUniform3f(colorLoc, 0.496f, 0.121f, 0.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);



		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.8f, 0.2f));
		model = glm::translate(model, glm::vec3(1.4f, -1.1f, 4.0f));

		glUniform3f(colorLoc, 0.949f, 0.933f, 0.621f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.21f, 0.21f, 0.21f));
		model = glm::translate(model, glm::vec3(1.35f, -5.6f, 3.8f));

		glUniform3f(colorLoc, 0.496f, 0.121f, 0.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Ubres

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.6f, 0.2f, 0.6f));
		model = glm::translate(model, glm::vec3(0.0f, -3.5f, 0.0f));

		glUniform3f(colorLoc, 1.0f, 0.414f, 0.246f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(1.0f, -4.5f, 1.0f));

		glUniform3f(colorLoc, 1.0f, 0.414f, 0.246f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(-1.0f, -4.5f, 1.0f));

		glUniform3f(colorLoc, 1.0f, 0.414f, 0.246f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(1.0f, -4.5f, -1.0f));

		glUniform3f(colorLoc, 1.0f, 0.414f, 0.246f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(-1.0f, -4.5f, -1.0f));

		glUniform3f(colorLoc, 1.0f, 0.414f, 0.246f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cabeza

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.9f, 1.0f,0.7f));
		model = glm::translate(model, glm::vec3(0.0f, 1.1f, 0.93f));

		glUniform3f(colorLoc, 0.496f, 0.121f, 0.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cuernos

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.9f, 0.25f, 0.25f));
		model = glm::translate(model, glm::vec3(0.0f, 6.8f, 2.8f));

		glUniform3f(colorLoc, 0.949f, 0.933f, 0.621f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.255f, 0.255f));
		model = glm::translate(model, glm::vec3(0.0f, 6.7f, 2.75f));

		glUniform3f(colorLoc, 0.496f, 0.121f, 0.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Orejas

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.5f, 0.35f, 0.3f));
		model = glm::translate(model, glm::vec3(0.0f, 3.6f, 2.2f));

		glUniform3f(colorLoc, 0.496f, 0.121f, 0.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.3f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(0.0f, 6.4f, 3.7f));

		glUniform3f(colorLoc, 0.765f, 0.347f, 0.210f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Hocico

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.7f, 0.1f, 0.4f));
		model = glm::translate(model, glm::vec3(0.0f, 11.0f, 2.8f));

		glUniform3f(colorLoc, 1.0f, 0.414f, 0.246f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.7f, 0.2f, 0.4f));
		model = glm::translate(model, glm::vec3(0.0f, 4.3f, 2.8f));

		glUniform3f(colorLoc, 1.0f, 0.414f, 0.246f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.4f));
		model = glm::translate(model, glm::vec3(3.0f, 10.0f, 2.8f));

		glUniform3f(colorLoc, 1.0f, 0.414f, 0.246f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.4f));
		model = glm::translate(model, glm::vec3(-3.0f, 10.0f, 2.8f));

		glUniform3f(colorLoc, 1.0f, 0.414f, 0.246f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 0.1f, 0.4f));
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 2.8f));

		glUniform3f(colorLoc, 1.0f, 0.414f, 0.246f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.7f, 0.15f, 0.2f));
		model = glm::translate(model, glm::vec3(0.0f, 4.2f, 5.5f));

		glUniform3f(colorLoc, 1.0f, 0.414f, 0.246f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.2f));
		model = glm::translate(model, glm::vec3(1.84f, 4.8f, 5.5f));

		glUniform3f(colorLoc, 1.0f, 0.414f, 0.246f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.2f));
		model = glm::translate(model, glm::vec3(-1.84f, 4.8f, 5.5f));

		glUniform3f(colorLoc, 1.0f, 0.414f, 0.246f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Ojos 

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.1f));
		model = glm::translate(model, glm::vec3(-1.0f, 5.2f, 10.5f));

		glUniform3f(colorLoc, 0.8f, 0.8f, 0.8f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::translate(model, glm::vec3(-2.4f, 13.0f, 11.0f));

		glUniform3f(colorLoc, 0.496f, 0.121f, 0.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);



		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.1f));
		model = glm::translate(model, glm::vec3(1.0f, 5.2f, 10.5f));

		glUniform3f(colorLoc, 0.8f, 0.8f, 0.8f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::translate(model, glm::vec3(2.4f, 13.0f, 11.0f));

		glUniform3f(colorLoc, 0.496f, 0.121f, 0.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.005f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.005f;
	 if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		 movY += 0.005f;
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 movY -= 0.005f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.2f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.2f;
 }


