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

	//	Run game logic init
	//Start();

	float _tempRainbowMultiplier = 0.0f;

	//	Run as long as the window is open
	while (!glfwWindowShouldClose(window)) {
		//	Clear the screen
		glClearColor(0.0f + 1 * glm::sin(_tempRainbowMultiplier + 32), 0.0f + 1 * glm::sin(_tempRainbowMultiplier + 11), 0.0f + 1 * glm::sin(_tempRainbowMultiplier + 4325), 1.0f);

		//	Clear color buffer	
		glClear(GL_COLOR_BUFFER_BIT);
		
		_tempRainbowMultiplier += 0.01f;

		//	==================================
		//			OpenGL Draw calls
		//	==================================

		//	Run game logic
		//Update();
		//	Swap the screen buffers
		glfwSwapBuffers(window);
		//	Poll for events
		glfwPollEvents();
	}

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