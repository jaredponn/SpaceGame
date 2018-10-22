#include <stdio.h>
#include "LLSRender.h"
#include "Lib/Logger.h"

// -----------------------------------------
//    private
// -----------------------------------------

static inline unsigned int
LLS_safeCreateAndCompileShader(const GLchar *shaderSource, GLenum shaderType);

// -----------------------------------------
//    public functions
// -----------------------------------------
unsigned int LLS_safeCreateAndCompileVertexShader(const GLchar *shaderSource)
{

	return LLS_safeCreateAndCompileShader(shaderSource, GL_VERTEX_SHADER);
}

unsigned int LLS_safeCreateAndCompileFragmentShader(const GLchar *shaderSource)
{

	return LLS_safeCreateAndCompileShader(shaderSource, GL_FRAGMENT_SHADER);
}

unsigned int LLS_safeLinkVertexAndFragmentShader(unsigned int vertexShader,
						 unsigned int fragmentShader)
{
	unsigned int shaderProgram = LLS_glCreateProgram();
	LLS_glAttachShader(shaderProgram, vertexShader);
	LLS_glAttachShader(shaderProgram, fragmentShader);

	LOG_OPENGL_SHADER_LINK_STATUS(shaderProgram);

	return shaderProgram;
}


// -----------------------------------------
//    Private implenetation
// -----------------------------------------
static inline unsigned int
LLS_safeCreateAndCompileShader(const GLchar *shaderSource, GLenum shaderType)
{

	unsigned int shader = LLS_glCreateShader(shaderType);
	LLS_glShaderSource(shader, 1, &shaderSource, NULL);
	LLS_glCompileShader(shader);

	LOG_OPENGL_SHADER_COMPILE_STATUS(shader)

	return shader;
}
