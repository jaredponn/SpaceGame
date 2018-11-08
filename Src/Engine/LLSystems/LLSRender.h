#pragma once

#include "Extern/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
/** Render.h
 * functions for rendering / dealing with the viewport
 */

/** Notes on openGL rendering: NDC are from 0 to 1
 * (0,0) -> bottom left corner
 * (1,1) -> upper right corner
 * viewport describes the transform from NDC to window coordinates
 */
// -----------------------------------------
//    functions
// -----------------------------------------


// -----------------------------------------
//    shader stuff
// -----------------------------------------
// convenience function for creating, and compilinga vertex shader, with error
// input if it fails creating the shader
unsigned int LLS_safeCreateAndCompileVertexShader(const GLchar *shaderSource);
unsigned int LLS_safeCreateAndCompileFragmentShader(const GLchar *shaderSource);

// links the program together
unsigned int LLS_safeLinkVertexAndFragmentShader(unsigned int vertexShader,
						 unsigned int fragmentShader);

// -----------------------------------------
//    Wrappers
// -----------------------------------------
// MUST be called AFTER makeContextcurrent in Window.h
// error handling is tested with if (! {..})) { ERROR HANDLING}
static inline int LLS_gladLoadGLLoader()
{
	return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

// glfwSwapBuffers
static inline void LLS_glSwapBuffers(GLFWwindow *window)
{

	glfwSwapBuffers(window);
}

// wrapper for glClearColor - fillsthe backgrond color, r, g, b, opacity
static inline void LLS_glClearColor(float r, float g, float b, float alpha)
{
	glClearColor(r, g, b, alpha);
}

// wrapper for glClear
static inline void LLS_glClear(GLbitfield mask)
{
	glClear(mask);
}

// wrapper for glGenBuffers
static inline void LLS_glGenBuffers(GLsizei n, GLuint *buffers)
{
	glGenBuffers(n, buffers);
}

// wrapper for glBindBuffer
static inline void LLS_glBindBuffer(GLenum target, GLuint buffer)
{
	glBindBuffer(target, buffer);
}

// wrapper for glBufferData
static inline void LLS_glBufferData(GLenum target, GLsizeiptr size,
				    const GLvoid *data, GLenum usage)
{
	glBufferData(target, size, data, usage);
}

// wrapper for glCreateShader
static inline unsigned int LLS_glCreateShader(GLenum shaderType)
{
	return glCreateShader(shaderType);
}

// wrapper for glShaderSource
static inline void LLS_glShaderSource(GLuint shader, GLsizei count,
				      const GLchar **string,
				      const GLint *length)
{
	glShaderSource(shader, count, string, length);
}

// wrapper for glCompileShader
static inline void LLS_glCompileShader(GLuint shader)
{
	glCompileShader(shader);
}


// wrapper for glCreateProgram()
static inline unsigned int LLS_glCreateProgram()
{
	return glCreateProgram();
}

// wrapper for glAttachShader()
static inline void LLS_glAttachShader(GLuint program, GLuint shader)
{
	glAttachShader(program, shader);
}

// wrapper for glBindFragDataLocation()
static inline void
LLS_glBindFragDataLocation(GLuint program, GLuint colorNumber, const char *name)
{
	glBindFragDataLocation(program, colorNumber, name);
}

// wrapper for glLinkProgram()
static inline void LLS_glLinkProgram(GLuint program)
{
	glLinkProgram(program);
}

// wrapper for glUseProgram()
static inline void LLS_glUseProgram(GLuint program)
{
	glUseProgram(program);
}

// wrapper for glGetAttribLocation()
static inline int LLS_glGetAttribLocation(GLuint program, const GLchar *name)
{
	return glGetAttribLocation(program, name);
}

// wrapper for glVertexAttribPointer
static inline void LLS_glVertexAttribPointer(GLuint index, GLint size,
					     GLenum type, GLboolean normalized,
					     GLsizei stride,
					     const GLvoid *pointer)
{
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

// wrapper for glEnableVertexAttribArray
static inline void LLS_glEnableVertexAttribArray(GLuint index)
{
	glEnableVertexAttribArray(index);
}

// wrapper for glGenVertexArrays
static inline void LLS_glGenVertexArrays(GLsizei n, GLuint *arrays)
{
	glGenVertexArrays(n, arrays);
}

// wrapper for glBindVertexArray
static inline void LLS_glBindVertexArray(GLuint vao)
{
	glBindVertexArray(vao);
}

static inline void LLS_glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
	glDrawArrays(mode, first, count);
}

static inline void LLS_glDeleteBuffers(GLsizei n, const GLuint *ids)
{
	glDeleteBuffers(n, ids);
}

static inline void LLS_glDisableVertexAttribArray(GLuint index)
{
	glDisableVertexAttribArray(index);
}

static inline void LLS_glDeleteShader(unsigned int shader)
{
	glDeleteShader(shader);
}
