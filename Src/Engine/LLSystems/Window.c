#include "Window.h"

// -----------------------------------------
//    Macros
// -----------------------------------------
#define UNUSED(val) (void)val

// -----------------------------------------
//    private
// -----------------------------------------
static inline void defaultFramebufferSizeCallback(GLFWwindow *window, int width,
						  int height);

// -----------------------------------------
//    functions
// -----------------------------------------

GLFWwindow *LLS_createWindow(const int width, const int height,
			     const char *title)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = LLS_glfwCreateWindow(width, height, title);

	return window;
}

void LLS_setDefaultFramebufferSizeCallback(GLFWwindow *window)
{
	glfwSetFramebufferSizeCallback(window, defaultFramebufferSizeCallback);
}

// -----------------------------------------
//    private implementations
// -----------------------------------------

static inline void defaultFramebufferSizeCallback(GLFWwindow *window, int width,
						  int height)
{
	// changes the viewport to match the windows dimensions
	UNUSED(window);
	glViewport(0, 0, width, height);
}

#undef UNUSED
