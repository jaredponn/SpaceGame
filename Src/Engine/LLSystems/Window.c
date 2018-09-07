#include "Window.h"

GLFWwindow *LLS_createWindow(const int width, const int height,
			     const char *title)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);

	return window;
}

void LLS_makeContextCurrent(GLFWwindow *window)
{
	glfwMakeContextCurrent(window);
}

bool LLS_shouldWindowClose(GLFWwindow *window)
{
	return glfwWindowShouldClose(window);
}

void LLS_destroyWindow(GLFWwindow *window)
{
	glfwDestroyWindow(window);
}
