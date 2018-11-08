#include "LLSInput.h"


void LLS_setKeyboardCallback(GLFWwindow *window,
			     void (*key_callback)(GLFWwindow *window, int key,
						  int scancode, int action,
						  int mods))
{
	glfwSetKeyCallback(window, key_callback);
}

void LLS_pollEvents()
{
	glfwPollEvents();
}
