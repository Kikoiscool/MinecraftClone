#pragma once
#ifndef VBO_CLASS
#define VBO_CLASS

#include <glad/glad.h>

class VBO {

public:

	//	VBO ident
	GLuint ID;

	//	Constructor
	VBO();
	VBO(GLfloat* vertices, GLsizeiptr size);

	//	Generates VBO
	void Generate();
	//	Binds VBO
	void Bind();
	//	Unbinds VBO
	void Unbind();
	//	Deletes VBO
	void Delete();

	//	Sets VBO data
	void SetData(GLfloat* vertices, GLsizeiptr size);
	void SetData(GLuint* vertices, GLsizeiptr size);
};

#endif