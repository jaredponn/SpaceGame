#pragma once

#include <GLFW/glfw3.h>
#include <stdbool.h>

/** Window.h
 * low level wrapper system functions for things dealing with GLFW and window
 * management. Provides higher level abstractions as well.
 */


// -----------------------------------------
//    Procedures
// -----------------------------------------

// creates a window and setes the glfw window hints. May return NULL
GLFWwindow *LLS_createWindow(const int width, const int height,
			     const char *title);

// sets a sefault framebuffer size callback
void LLS_setDefaultFramebufferSizeCallback(GLFWwindow *window);


// -----------------------------------------
//    Wrappers
// -----------------------------------------

// makes the selected window have a OpenGL context
static inline void LLS_glfwMakeContextCurrent(GLFWwindow *window)
{
	glfwMakeContextCurrent(window);
}

static inline void LLS_glfwSetSwapInterval(unsigned int n)
{

	glfwSwapInterval(n);
}

// returns true if user wants to close the window
static inline bool LLS_glfwShouldWindowClose(GLFWwindow *window)
{

	return glfwWindowShouldClose(window);
}

// destroys window
static inline void LLS_glfwDestroyWindow(GLFWwindow *window)
{
	glfwDestroyWindow(window);
}

static inline void
LLS_glfwSetFramebufferSizeCallback(GLFWwindow *window,
				   GLFWframebuffersizefun cbfun)
{
	glfwSetFramebufferSizeCallback(window, cbfun);
}

static inline GLFWwindow *
LLS_glfwCreateWindow(const int width, const int height, const char *title)
{

	return glfwCreateWindow(width, height, title, NULL, NULL);
}
