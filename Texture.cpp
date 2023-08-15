#include "Texture.h"
#include <iostream>
#include <lodepng/lodepng.h>
#include <stb/stb_image.h>

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	//->texType;
	this->slot = slot;

	//const char* filepath = "sample.png";
	//
	//unsigned w, h;
	//
	//std::vector<unsigned char> data;
	//
	//// Load image
	//unsigned int error = lodepng::decode(data, w, h, filepath);

	stbi_set_flip_vertically_on_load(true);
	int w, h, channels;
	unsigned char* data = stbi_load(image, &w, &h, &channels, 0);

	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, w, h, 0, format, GL_UNSIGNED_BYTE, &data);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, format, pixelType, data);

	stbi_image_free(data);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
