#include "Window.h"
#include <SDL2/SDL.h>
#include "Lib/V2.h"


struct V2 INP_getScreenSize()
{
	SDL_DisplayMode mode;
	if (SDL_GetCurrentDisplayMode(0, &mode) == 0) {
		return (struct V2){.x = mode.w, .y = mode.h};
	} else {
		// TODO maybe addsome proper error handling
		printf("\nerror getting screen size in " __FILE__ "\n");
		return (struct V2){.x = mode.w, .y = mode.h};
	}
}
