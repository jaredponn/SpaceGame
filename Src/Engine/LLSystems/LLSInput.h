#pragma once

#include <GLFW/glfw3.h>

/** LLSInput.h
 * wrappers for GLFW's input stuff
 */

// -----------------------------------------
//    Procedures
// -----------------------------------------

// sets the key callback function
void LLS_setKeyboardCallback(GLFWwindow *window,
			     void (*key_callback)(GLFWwindow *window, int key,
						  int scancode, int action,
						  int mods));

// polls the events
void LLS_pollEvents();


// basic example call back func:
/*
 static void key_callback(GLFWwindow *window, int key, int scancode, int
action,
			 int mods)
{
	 if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		 glfwSetWindowShouldClose(window, GLFW_TRUE);
 }
 */
