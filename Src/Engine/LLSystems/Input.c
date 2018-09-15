#include "Input.h"
#include "stdio.h"


// -----------------------------------------
//    Macros
// -----------------------------------------

// max keybaor dkeyts
#define MAX_KEYBOARD_KEY_NUMBER GLFW_KEY_MENU

// don't forget about hemouse
//#define MAX_KEYBOARD_KEY_NUMBER GLFW_KEY_MENU

#define UNUSED(var) (void)var

// bit mask for the bits
#define INPUT_STATE_BIT_MASK INP_DOWN

// -----------------------------------------
//    static variables
// -----------------------------------------

static unsigned int KEYBOARD_KEY_BUFFER[MAX_KEYBOARD_KEY_NUMBER] = {0};

// -----------------------------------------
//    Private functions
// -----------------------------------------

// shifts the bits of the input buffers left one. Must be called once every
// frame
static inline void INP_shiftInputBuffers();

// -----------------------------------------
//    Functions
// -----------------------------------------

void INP_pollAndUpdateInputBuffer()
{
	INP_shiftInputBuffers();
	LLS_pollEvents();
}


void INP_defaultKeyboardCallback(GLFWwindow *window, int key, int scancode,
				 int action, int mods)
{
	// surpressing compiler warnings
	UNUSED(window);
	UNUSED(scancode);
	UNUSED(mods);

	// does not modify the keyboard buffer if the key is unknown
	if (key == GLFW_KEY_UNKNOWN)
		return;

	switch (action) {
	case GLFW_PRESS:
		KEYBOARD_KEY_BUFFER[key] |= 1;
		break;

	case GLFW_RELEASE:
		KEYBOARD_KEY_BUFFER[key] <<= 1;
		break;

	case GLFW_REPEAT:
		break;
	}
}


enum INP_States getKeyboardKeyState(unsigned int key)
{
	enum INP_States keyState =
		INPUT_STATE_BIT_MASK & KEYBOARD_KEY_BUFFER[key];
	return keyState;
}


void INP_printKeyboardKeyState(enum INP_States state)
{
	switch (state) {
	case INP_UP:
		printf("Key is UP");
		break;
	case INP_PRESS:
		printf("Key is PRESSED");
		break;
	case INP_DOWN:
		printf("Key is DOWN");
		break;
	case INP_RELEASE:
		printf("Key is RELEASED");
		break;
	default:
		printf("Unknown state: %i", state & INPUT_STATE_BIT_MASK);
		break;
	}
	printf("\n");
}

// -----------------------------------------
//    Private functions
// -----------------------------------------

static inline void INP_shiftInputBuffers()
{
	unsigned int firstBit;

	for (unsigned int i = 0; i < MAX_KEYBOARD_KEY_NUMBER; ++i) {
		firstBit = 0x1 & KEYBOARD_KEY_BUFFER[i];
		KEYBOARD_KEY_BUFFER[i] =
			(KEYBOARD_KEY_BUFFER[i] << 1) | firstBit;
	}
}

#undef UNUSED
#undef MAX_KEYBOARD_KEY_NUMBER
#undef INPUT_STATE_BIT_MASK
