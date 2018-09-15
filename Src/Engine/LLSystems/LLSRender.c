#include <stdio.h>
#include "LLSRender.h"


void LLS_updateViewport(GLFWwindow *window)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	/** printf("width: %i\n", width); */
	/** printf("height: %i\n", height); */
	glViewport(0, 0, width, height);
}

int LLS_loadGLLoader()
{
	return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void LLS_swapBuffers(GLFWwindow *window)
{
	glfwSwapBuffers(window);
}

void LLS_clearColor(float r, float g, float b, float alpha)
{
	glClearColor(r, g, b, alpha);
}

void LLS_clear(GLbitfield mask)
{
	glClear(mask);
}

void LLS_genBuffers(GLsizei n, GLuint *buffers)
{
	glGenBuffers(n, buffers);
}


void LLS_bindBuffer(GLenum target, GLuint buffer)
{
	glBindBuffer(target, buffer);
}

void LLS_bufferData(GLenum target, GLsizeiptr size, const GLvoid *data,
		    GLenum usage)
{
	glBufferData(target, size, data, usage);
}
