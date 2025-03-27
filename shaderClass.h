#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename);

class Shader
{
	public:
		// Reference ID of the shader program
		GLuint ID;

		// Constructor that build the Shader Program from 2 different shaders
		Shader(const char* vertexFile, const char* fragmentFile);
		
		// Activates the shader program
		void Activate();

		// Deletes the shader program
		void Delete();
};
#endif