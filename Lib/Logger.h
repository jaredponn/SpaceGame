#pragma once

#include <stdio.h>
#include <GLFW/glfw3.h>

#include "Src/Debug.h"

/** Logger.h
 * Functions for logging
 */


// if logging is enabled, create a the godly logger macros, functions, and
// global variables
#ifdef GLOBAL_LOGGER_BOOL

// -----------------------------------------
// Constants
// -----------------------------------------

#define ERROR_LOG_BUFFER_SIZE 1024
static char ERROR_LOG_BUFFER[ERROR_LOG_BUFFER_SIZE] = {0};

// -----------------------------------------
//    Procedures
// -----------------------------------------

#define LOG_TEXT(log_level, ...)                                               \
	if (log_level <= LOG_LEVEL) {                                          \
		fprintf(stdout, __VA_ARGS__);                                  \
		fflush(stdout);                                                \
	}

#define LOG_OPENGL_SHADER_COMPILE_STATUS(shader)                               \
	do {                                                                   \
		GLint status;                                                  \
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);             \
		glGetShaderInfoLog(shader, ERROR_LOG_BUFFER_SIZE, NULL,        \
				   ERROR_LOG_BUFFER);                          \
		LOG_TEXT(0, ERROR_LOG_BUFFER)                                  \
	} while (0);

#define LOG_OPENGL_SHADER_LINK_STATUS(shader)                                  \
	do {                                                                   \
		GLint status;                                                  \
		glGetProgramiv(shader, GL_LINK_STATUS, &status);               \
		glGetShaderInfoLog(shader, ERROR_LOG_BUFFER_SIZE, NULL,        \
				   ERROR_LOG_BUFFER);                          \
		LOG_TEXT(0, ERROR_LOG_BUFFER)                                  \
	} while (0);


#endif

// if logging is not enabled, then just define everything to be empty
#ifndef GLOBAL_LOGGER_BOOL

#define LOG_TEXT(...)
#define LOG_OPENGL_SHADER_COMPILE_ERROR(...)

#endif
