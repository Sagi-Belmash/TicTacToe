#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO
{
	public:
		// Reference ID to the Element Buffer Object
		GLuint ID;

		// Constructor that generates the EBO and links it to the indices
		EBO(GLuint* indices, GLsizeiptr size);
		// Binds the EBO
		void Bind();
		// Unbinds the EBO
		void Unbind();
		// Deletes the EBO
		void Delete();
};

#endif