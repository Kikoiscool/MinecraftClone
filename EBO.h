#pragma once
#ifndef EBO_CLASS
#define EBO_CLASS

#include <glad/glad.h>

class EBO {

public:

	//	EBO ident
	GLuint ID;

	//	Constructor
	EBO();
	EBO(GLuint* indices, GLsizeiptr size);

	//	Generates EBO
	void Generate();
	//	Binds EBO
	void Bind();
	//	Unbinds EBO
	void Unbind();
	//	Deletes EBO
	void Delete();

	//	Sets EBO data
	void SetData(GLuint* indices, GLsizeiptr size);
};

#endif