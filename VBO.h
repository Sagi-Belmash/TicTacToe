#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
	public:
		// Referenece ID of the Vertex Buffer Object
		GLuint ID;

		// Default constructor that generates the VBO without linking it
		VBO();
		// Constructor that generates the VBO and links it to the vertices
		VBO(GLfloat* vertices, GLsizeiptr size);
		// Updates the VBO with new vertices
		void Update(GLfloat* vertices, GLsizeiptr size);
		// Binds the VBO
		void Bind();
		// Unbinds the VBO
		void Unbind();
		// Deletes the VBO
		void Delete();
};

#endif