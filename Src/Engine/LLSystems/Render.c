#include "Render.h"


void LLS_updateViewport(GLFWwindow *window)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

void LLS_swapBuffers(GLFWwindow *window)
{
	glfwSwapBuffers(window);
}
