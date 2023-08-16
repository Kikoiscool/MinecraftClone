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

void processInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double xPos, double yPos);

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;



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
	glfwSetCursorPosCallback(window, mouseCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//	Load GLAD so it configures OpenGL
	gladLoadGL();

	//	Tell OpenGL the size of the window
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);	

	Shader defaultShader("default.vert", "default.frag");
	defaultShader.Activate();

	GLuint vertices[]{
		0, 0, 0, 1, 0, 0, // RED 0
		0, 1, 0, 0, 1, 0, // GREEN 1
		1, 1, 0, 0, 0, 1, // BLUE 2
		1, 0, 0, 1, 1, 0, // YELLOW 3
		1, 0, 1, 0, 1, 1, // CYAN 4
		1, 1, 1, 1, 0, 1, // MAGENTA 5
		0, 1, 1, 1, 1, 1, // WHITE 6
		0, 0, 1, 0, 0, 0  // BLACK 7
	};

	GLuint indices[]{
		0, 1, 2, //	Front
		0, 2, 3,
		1, 6, 5, // Top
		1, 5, 2,
		4, 5, 6, // Back
		4, 6, 7,
		3, 4, 0, // Bottom
		4, 7, 0,
		3, 2, 5, // Right 
		3, 5, 4,
		7, 1, 0, // Left
		7, 6, 1
	};

	VAO defaultVAO = VAO();
	defaultVAO.Bind();

	VBO defaultVBO = VBO();
	defaultVBO.Bind();
	defaultVBO.SetData(vertices, sizeof(vertices));
	//defaultVBO.SetData(fvertices, sizeof(fvertices));

	EBO defaultEBO = EBO();
	defaultEBO.Bind();
	defaultEBO.SetData(indices, sizeof(indices));

	// Vertex positions
	//defaultVAO.AddAttr(&defaultVBO, 0, 3, GL_UNSIGNED_INT, 3 * sizeof(GLuint), (void*)0);
	
	// Vertex UV's
	//defaultVAO.AddAttr(&defaultVBO, 1, 2, GL_UNSIGNED_INT, 2 * sizeof(GLuint), (void*)(3 * sizeof(GLuint)));
	//defaultVAO.AddAttr(&defaultVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	//defaultVAO.AddAttr(&defaultVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	defaultVAO.AddAttr(&defaultVBO, 0, 3, GL_UNSIGNED_INT, 6 * sizeof(GLuint), (void*)0);
	defaultVAO.AddAttr(&defaultVBO, 1, 3, GL_UNSIGNED_INT, 6 * sizeof(GLuint), (void*)(3 * sizeof(GLuint)));

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

	//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	//glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));

	//vec = trans * vec;

	//glm::mat4 trans = glm::mat4(1.0f);

	//glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	//glm::mat4 view = glm::mat4(1.0f);
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	//glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	//
	//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	//glm::vec3 cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection));
	//glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	//
	//glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	//	Run as long as the window is open
	while (!glfwWindowShouldClose(window)) {
		
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		//	Clear the screen
		glClearColor(0.0f + 1 * glm::sin(_tempRainbowMultiplier + 322), 0.0f + 1 * glm::sin(_tempRainbowMultiplier + 10291), 0.0f + 1 * glm::sin(_tempRainbowMultiplier + 5), 1.0f);

		//	Clear color buffer	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	

		//trans = glm::mat4(1.0f);
		//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		//trans = glm::rotate(trans, (float)glfwGetTime(),glm::vec3(0.0f, 0.0f, 1.0f));

		//glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
		
		//model = glm::rotate(model, glm::radians(_tempRainbowMultiplier) * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		
		_tempRainbowMultiplier += 0.01f;

		processInput(window);

		//	==================================
		//			OpenGL Draw calls
		//	==================================

		//	Bind texture
		
		defaultShader.Activate();
		defaultTexture.Bind();
		defaultVAO.Bind();
		
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);

		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 view = glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp);
		glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));


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

////	Start is called once on load
//void Start() {
//
//}
//
////	Update is called once per frame
//void Update() {
//	
//}
//
////	OnUnload is called once on close
//void OnUnload() {
//
//}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		if(glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}


	float cameraSpeed = static_cast<float>(2.5 * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	float xpos = static_cast<float>(xPos);
	float ypos = static_cast<float>(yPos);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}
