#include "VBO.h"

VBO::VBO()
{
	Generate();
}

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	Generate();
	SetData(vertices, size);
}

void VBO::Generate()
{
	glGenBuffers(1, &ID);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}

void VBO::SetData(GLfloat* vertices, GLsizeiptr size)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::SetData(GLuint* vertices, GLsizeiptr size)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

