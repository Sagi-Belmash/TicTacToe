#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
	public:
		// Reference ID to the Vertex Array Object
		GLuint ID;

		// Constuctor that generates a VAO ID
		VAO();
		// Link a VBO to the VAO using a certain layout
		void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLuint stride, void* offset);
		// Binds the VAO
		void Bind();
		// Unbinds the VAO
		void Unbind();
		// Deletes the VAO
		void Delete();
};

#endif