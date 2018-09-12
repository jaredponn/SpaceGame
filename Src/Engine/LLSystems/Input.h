#include "LLSInput.h"

/** Input.h
 * Higher level wrapper for GLFW's input stuff
 */

// -----------------------------------------
//    Macros
// -----------------------------------------

#define MAX_KEYBOARD_KEY_NUMBER GLFW_KEY_MENU

// don't forget about hemouse
#define MAX_KEYBOARD_KEY_NUMBER GLFW_KEY_MENU

// -----------------------------------------
//    Procedures
// -----------------------------------------

// shifts the bits of the input buffers left one. Must be called once every
// frame
void INP_updateInputBuffers();

// default key callback that uses the KEYBOARD_KEY_BUFFER
void INP_defaultKeyCallback(GLFWwindow *window, int key, int scancode,
			    int action, int mods);
