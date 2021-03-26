#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "GL\glew.h"
#include "GL\freeglut.h"

#include "shaderLoader.h" //narzŕdzie do │adowania i kompilowania shaderˇw z pliku

//funkcje algebry liniowej
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective

//Wymiary okna
int screen_width = 640;
int screen_height = 640;

float triangle1[]{
	// positions			//colors
	-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	// left  top
	-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	// left  bottom
	 0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f	// right bottom
};

float triangle2[]{
	0.0f, 0.5f, 0.0f, // left  top
	0.5f, 0.0f, 0.0f, // right bottom
	0.5f, 0.5f, 0.0f  // right top
};

float border[]{
	-0.75f, 0.75f,  0.0f,  // left top
	-0.75f, -0.75f, 0.0f, // left bottom
	 0.75f, -0.75f, 0.0f, // right bottom
	 0.75f,  0.75f, 0.0f  // right top
};

unsigned int borderIndices[]{
	0, 1,
	1, 2,
	2, 3,
	3, 0
};


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(screen_width, screen_height);
	glutInitWindowPosition(0, 0); // pozycja okna
	glutCreateWindow("Learn");
	
	glewInit();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.0, 0.5, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	

	// SHADER PROGRAM 1
	unsigned int shaderProgram1;
	shaderProgram1 = loadShaders("vertex_shader.glsl", "fragment_shader1.glsl");
	glUseProgram(shaderProgram1);

	unsigned int VAOs[3];
	unsigned int VBOs[3];

	glGenVertexArrays(3, VAOs);
	glGenBuffers(3, VBOs);

	// VAO 1
	glBindVertexArray(VAOs[0]); // bind vao
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]); // bind vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW); // pass data

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // configure attributes
	glEnableVertexAttribArray(0); // enable attribute

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0); // unbind vao

	// VAO 2
	glBindVertexArray(VAOs[1]); // bind vao
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0); // unbind vao


	glBindVertexArray(VAOs[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(VAOs[1]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0); // unbind VAO

	// SHADER PROGRAM 2
	unsigned int shaderProgram2;
	shaderProgram2 = loadShaders("vertex_shader.glsl", "fragment_shader2.glsl");
	glUseProgram(shaderProgram2);

	int ourColorLocation = glGetUniformLocation(shaderProgram2, "ourColor");
	glUniform4f(ourColorLocation, 1.0f, 0.5f, 0.2f, 1.0f);
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAOs[2]); //bind vao
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(border), border, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(borderIndices), borderIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	
	glBindVertexArray(VAOs[2]);
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_LINES, 0, 4);
	glBindVertexArray(0); //unbind vao



	//// VAO - Vertex Array Object
	//unsigned int VAO;
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);

	//// VBO - Vertex Buffer Object
	//unsigned int VBO;
	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	////glDrawArrays(GL_TRIANGLES, 0, 3);
	//
	////// EBO - Element Buffer Object
	//unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	

	glutSwapBuffers();
	glutMainLoop();
	return(0);
}


