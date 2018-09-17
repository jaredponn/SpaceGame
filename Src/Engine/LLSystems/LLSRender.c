#include <stdio.h>
#include "LLSRender.h"
#include "Lib/Logger.h"

// -----------------------------------------
//    private
// -----------------------------------------
static inline void LLS_safeCreateAndCompileShader(const GLchar *shaderSource,
						  GLenum shaderType);

// -----------------------------------------
//    public functions
// -----------------------------------------

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

unsigned int LLS_createShader(GLenum shaderType)
{
	return glCreateShader(shaderType);
}

void LLS_shaderSource(GLuint shader, GLsizei count, const GLchar **string,
		      const GLint *length)
{
	glShaderSource(shader, count, string, length);
}

void LLS_compileShader(GLuint shader)
{
	glCompileShader(shader);
}

void LLS_safeCreateAndCompileVertexShader(const GLchar *shaderSource)
{
	LLS_safeCreateAndCompileShader(shaderSource, GL_VERTEX_SHADER);
}

void LLS_safeCreateAndCompileFragementShader(const GLchar *shaderSource)
{

	LLS_safeCreateAndCompileShader(shaderSource, GL_FRAGMENT_SHADER);
}
// -----------------------------------------
//    Private implenetation
// -----------------------------------------
static inline void LLS_safeCreateAndCompileShader(const GLchar *shaderSource,
						  GLenum shaderType)
{

	unsigned int shader = LLS_createShader(shaderType);
	LLS_shaderSource(shader, 1, &shaderSource, NULL);
	LLS_compileShader(shader);

	LOG_OPENGL_SHADER_COMPILE_STATUS(shader)
}
