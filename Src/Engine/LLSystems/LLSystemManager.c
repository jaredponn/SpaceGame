#include "LLSystemManager.h"
#include "stdio.h"

// -----------------------------------------
//    private
// -----------------------------------------

static inline void defaultErrorCallback(int error, const char *description);

// -----------------------------------------
//    public functions
// -----------------------------------------

void LLS_setErrorCallback(void (*error_callback)(int error,
						 const char *description))
{
	glfwSetErrorCallback(error_callback);
}

void LLS_setDefaultErrorCallback()
{
	glfwSetErrorCallback(defaultErrorCallback);
}


bool LLS_initGraphicsLibFrameWork()
{
	return glfwInit();
}

void LLS_terminateGraphicsLibFrameWork()
{
	glfwTerminate();
}

// -----------------------------------------
//    private
// -----------------------------------------

static inline void defaultErrorCallback(int error, const char *description)
{
	fprintf(stderr, "GLFW Error (%i): %s \n", error, description);
}
