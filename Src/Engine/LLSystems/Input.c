#include "Input.h"
#include "stdio.h"

#define UNUSED(var) (void)var


static unsigned int KEYBOARD_KEY_BUFFER[MAX_KEYBOARD_KEY_NUMBER] = {0};

void INP_defaultKeyCallback(GLFWwindow *window, int key, int scancode,
			    int action, int mods)
{
	// does does not modify the keyboard buffer if the key is unknown
	if (key == GLFW_KEY_UNKNOWN)
		return;

	UNUSED(window);
	UNUSED(scancode);
	UNUSED(mods);

	if (action == GLFW_PRESS) {
		printf("KEYIS PRESED\n");
		KEYBOARD_KEY_BUFFER[key] |= 1;
	}
}
