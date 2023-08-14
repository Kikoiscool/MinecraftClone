#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>

#include "Shader.h"

class Texture {

public:
	GLuint ID;
	//GLuint* texType;
	GLuint slot;

	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();


};

#endif