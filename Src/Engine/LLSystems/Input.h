#include "LLSInput.h"

/** Input.h
 * Higher level wrapper for GLFW's input stuff.
 * NOTE: there is a bug here that during the INP_PRESS and INP_RELEASE state
 * there will be an "invalid" key state for 2 frames, where the bit buffer will
 * not have a valid key state. This shouldn't affect anything, but be aware that
 * it does exist.
 */


// -----------------------------------------
//    types
// -----------------------------------------

enum INP_States {
	INP_UP = 0x0,	 // 0b00
	INP_PRESS = 0b0011,   // 0b01
	INP_DOWN = 0b1111,    // 0b11
	INP_RELEASE = 0b1100, // 0b10
	INP_UNKNOWN
};

// -----------------------------------------
//    Procedures
// -----------------------------------------

// polls, and shifts the input buffers
void INP_pollAndUpdateInputBuffer();

// default key callback that uses the KEYBOARD_KEY_BUFFER
void INP_defaultKeyboardCallback(GLFWwindow *window, int key, int scancode,
				 int action, int mods);

// getsa specified key's keybaord state. unsigned int "key" should be GLFW macro
// corrosponding to the key
enum INP_States getKeyboardKeyState(unsigned int key);


// prints the key state ofa key
void INP_printKeyboardKeyState(enum INP_States state);
