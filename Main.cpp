#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

int main() {
	//	Initialize GLFW
	glfwInit();

	//	Tell GLFW what version of OpenGL we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 800;
	
	//	Create a GLFWwindow object
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Minecraft Clone ;)", NULL, NULL);

	//	Error check if the window fails to create
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//	Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//	Load GLAD so it configures OpenGL
	gladLoadGL();

	//	Tell OpenGL the size of the window
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);	

	Shader defaultShader("default.vert", "default.frag");
	defaultShader.Activate();

	GLuint vertices[] = {
		0, 0, 0,	//	0
		1, 0, 0,	//	1
		1, 1, 0,	//	2
		0, 1, 0,	//	3
	};
	
	GLuint t_vertices[] = {
	0, 0, 0, 0, 0,	//	0
	1, 0, 0, 1, 0,	//	1
	1, 1, 0, 1, 1,	//	2
	0, 1, 0, 0, 1	//	3
	};

	GLfloat fvertices[] = {
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,	1.0f, 0.0f  // Lower right corner
	};

	GLfloat _fvertices[] = {
	-0.5f, -0.5f, 0.0f,	//	0
	-0.5f, 0.5f, 0.0f,	//	1
	0.5f, 0.5f, 0.0f,	//	2
	0.5f, -0.5f, 0.0f,//	3
	};

	GLuint indices[] = {
		0, 2, 1,
		0, 3, 2
	};

	VAO defaultVAO = VAO();
	defaultVAO.Bind();

	VBO defaultVBO = VBO();
	defaultVBO.Bind();
	defaultVBO.SetData(fvertices, sizeof(fvertices));
	//defaultVBO.SetData(fvertices, sizeof(fvertices));

	EBO defaultEBO = EBO();
	defaultEBO.Bind();
	defaultEBO.SetData(indices, sizeof(indices));

	// Vertex positions
	//defaultVAO.AddAttr(&defaultVBO, 0, 3, GL_UNSIGNED_INT, 3 * sizeof(GLuint), (void*)0);
	
	// Vertex UV's
	//defaultVAO.AddAttr(&defaultVBO, 1, 2, GL_UNSIGNED_INT, 2 * sizeof(GLuint), (void*)(3 * sizeof(GLuint)));
	defaultVAO.AddAttr(&defaultVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	defaultVAO.AddAttr(&defaultVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	defaultShader.Activate();

	Texture defaultTexture = Texture("sample.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	defaultTexture.texUnit(defaultShader, "tex0", 0);

	defaultShader.Activate();
	

	//defaultVAO.Unbind();
	//defaultVBO.Unbind();
	//defaultEBO.Unbind();

	//	Run game logic init
	//Start();

	

	//	==================================
	//			Main loop
	//	==================================

	float _tempRainbowMultiplier = 0.0f;

	defaultVAO.Bind();


	//	Run as long as the window is open
	while (!glfwWindowShouldClose(window)) {
		//	Clear the screen
		glClearColor(0.0f + 1 * glm::sin(_tempRainbowMultiplier + 322), 0.0f + 1 * glm::sin(_tempRainbowMultiplier + 10291), 0.0f + 1 * glm::sin(_tempRainbowMultiplier + 5), 1.0f);

		//	Clear color buffer	
		glClear(GL_COLOR_BUFFER_BIT);
		
		_tempRainbowMultiplier += 0.01f;

		//	==================================
		//			OpenGL Draw calls
		//	==================================

		//	Bind texture
		
		defaultShader.Activate();
		defaultTexture.Bind();
		defaultVAO.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//	Run game logic
		//Update();
		//	Swap the screen buffers
		glfwSwapBuffers(window);
		//	Poll for events
		glfwPollEvents();
	}

	defaultShader.Delete();

	return 0;
}

//	Start is called once on load
void Start() {

}

//	Update is called once per frame
void Update() {
	
}

//	OnUnload is called once on close
void OnUnload() {

}