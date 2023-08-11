#include "VAO.h"

VAO::VAO()
{
	Generate();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}

void VAO::AddAttr(VBO* VBO, unsigned int layout, unsigned int numComponents, unsigned int type, GLsizeiptr stride, void* offset)
{
	VBO->Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride , offset);
	glEnableVertexAttribArray(layout);
	VBO->Unbind();
}

void VAO::Generate()
{
	glGenVertexArrays(1, &ID);
}
