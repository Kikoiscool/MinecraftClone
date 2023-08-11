#pragma once
#ifndef VAO_CLASS
#define VAO_CLASS

#include <glad/glad.h>
#include "VBO.h"

class VAO {
public:

	//	VAO ident
	GLuint ID;

	//	Constructor
	VAO();

	//	Binds VAO
	void Bind();
	//	Unbinds VAO
	void Unbind();
	//	Deletes VAO
	void Delete();

	//	Adds attributes
	void AddAttr(VBO* VBO, unsigned int layout, unsigned int numComponents, unsigned int type, GLsizeiptr stride, void* offset);

private:
	void Generate();

};

#endif