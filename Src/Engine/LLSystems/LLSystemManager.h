#pragma once

#include <GLFW/glfw3.h>
#include <stdbool.h>

/** LLSystemManager.h
 * Includes wrapperfuntions for GLFW initialization, and destruction
 */

// -----------------------------------------
//    Procedures
// -----------------------------------------

// sets the error callback of GLFW. MUST be called before LLS_initGraphicsLib();
void LLS_setErrorCallback(void (*error_callback)(int error,
						 const char *description));

// sets the default error callback to simply print stderr
void LLS_setDefaultErrorCallback();

// initlizes the graphics lib framework library (GLFW)
// also sets the swap interval to 1 for glfwSwapBuffers
bool LLS_initGraphicsLibFrameWork();

// terminates GLFW
void LLS_terminateGraphicsLibFrameWork();
