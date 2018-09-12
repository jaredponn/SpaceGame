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

// creates a window. May return NULL
GLFWwindow *LLS_createWindow(const int width, const int height,
			     const char *title);

// makes the selected window have a OpenGL context
// ALSO sets the swap interval to 1
void LLS_makeContextCurrent(GLFWwindow *);

void LLS_setSwapInterval(unsigned int);

// returns true if user wants to close the window
bool LLS_shouldWindowClose(GLFWwindow *);

// destroys window
void LLS_destroyWindow(GLFWwindow *);
