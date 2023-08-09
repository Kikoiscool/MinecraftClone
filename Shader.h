#pragma once

#ifndef SHADER_CLASS
#define SHADER_CLASS

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

class Shader {


public:
	//	Program ident
	GLuint ID;

	//	Constructor that builds the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	//	Activates the Shader Program
	void Activate();

	//	Deletes the Shader Program
	void Delete();

private:

	const unsigned int ERR_VERTEX = 0x000001;
	const unsigned int ERR_FRAGMENT = 0x000002;
	const unsigned int ERR_PROGRAM = 0x000004;

	//	Checks to see if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, unsigned int type);

	
};

#endif