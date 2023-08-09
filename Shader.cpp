#include "Shader.h"
using namespace std;

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//	1. Retrieve the vertex/fragment source code from filePath
	string _vertexCode = get_shader_file_contents(vertexFile);
	string _fragmentCode = get_shader_file_contents(fragmentFile);

	//	2. Convert source code from string to const char*
	const char* _vertexCodeCStr = _vertexCode.c_str();
	const char* _fragmentCodeCStr = _fragmentCode.c_str();

	//	3. Compile Shaders

	//	-----------------
	//	Vertex Shader
	//	-----------------
	GLuint _vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertexShader, 1, &_vertexCodeCStr, NULL);
	glCompileShader(_vertexShader);
	compileErrors(_vertexShader, ERR_VERTEX);

	//	-------------------
	//	Fragment Shader
	//	-------------------
	GLuint _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragmentShader, 1, &_fragmentCodeCStr, NULL);
	glCompileShader(_fragmentShader);
	compileErrors(_fragmentShader, ERR_FRAGMENT);

	//	-------------------
	//	Shader Program
	//	-------------------
	ID = glCreateProgram();
	glAttachShader(ID, _vertexShader);
	glAttachShader(ID, _fragmentShader);
	glLinkProgram(ID);
	compileErrors(ID, ERR_PROGRAM);

	//	4. Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(_vertexShader);
	glDeleteShader(_fragmentShader);
}

void Shader::Activate()
{
	//	Uses the current shader
	glUseProgram(ID);
}

void Shader::Delete()
{
	//	Checks to see if the current shader is the one we want to delete, if so, unbinds it
	GLint _currentProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &_currentProgram);

	if(_currentProgram == ID)
		glUseProgram(0);
	
	//	Deletes the current shader
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, unsigned int type)
{
	//	Checks to see if the shader compiled properly
	int _success;
	char _infoLog[1024];

	if (type == ERR_PROGRAM)
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &_success);
		if (!_success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, _infoLog);
			cout << "Error: Shader program linking failed\n" << _infoLog << endl;
		}
	}
	else
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &_success);
		if (!_success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, _infoLog);
			if(type == ERR_VERTEX)
				cout << "[FATAL] Error: Vertex shader compilation failed\n" << _infoLog << endl;
			else if(type == ERR_FRAGMENT)
				cout << "[FATAL] Error: Fragment shader compilation failed\n" << _infoLog << endl;
		}
	}
}

string get_shader_file_contents(const char* path) {
	ifstream in(path, ios::in | ios::binary);
	if (in.rdstate() == (ios_base::badbit | ios_base::failbit)) {
		cout << "Error: " << strerror(errno) << endl;
		return "";
	}
	else if (in) {
		ostringstream contents;
		contents << in.rdbuf();
		in.close();
		return contents.str();
	}
	else {
		cout << "Error: " << strerror(errno) << endl;
		return "";
	}
}
