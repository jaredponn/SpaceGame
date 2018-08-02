#include "ResourceRegistry.h"
#include <SDL2/SDL_image.h>
#include "LoadResources.h"

// clang-format off
#define EXTRAS_PATH "/home/jared/Programs/SpaceGame/Extras"
// clang-format on

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

void ECS_destroyRegistry(struct ECS_ResourceRegistry *registry)
{
	SDL_DestroyRenderer(registry->renderer);
	registry->renderer = NULL;
	SDL_DestroyWindow(registry->window);
	registry->window = NULL;

	// destroying the textures
	SDL_DestroyTexture(registry->resources.textures.aabbDebugTexture);
	registry->resources.textures.aabbDebugTexture = NULL;
	SDL_DestroyTexture(registry->resources.textures.testTexture);
	registry->resources.textures.testTexture = NULL;
}

void ECS_loadInitResources(struct ECS_ResourceRegistry *resourceRegistry)
{
	SDL_Window *window = RSC_createInitWindow(
		"Space Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

	SDL_Renderer *renderer =
		RSC_createInitRenderer(window, SDL_RENDERER_ACCELERATED);

	// TODO add proper error handling
	SDL_Texture *testTexture =
		RSC_loadImage(renderer, EXTRAS_PATH "/Images/bg.png");

	SDL_Texture *planet1 = RSC_loadImage(renderer, EXTRAS_PATH
					     "/Images/500x500circ-01.png");
	SDL_Texture *planet2 = RSC_loadImage(renderer, EXTRAS_PATH
					     "/Images/500x500circ-02.png");
	SDL_Texture *planet3 = RSC_loadImage(renderer, EXTRAS_PATH
					     "/Images/500x500circ-03.png");
	SDL_Texture *planet4 = RSC_loadImage(renderer, EXTRAS_PATH
					     "/Images/500x500circ-04.png");

	// TODO PROPERLY DEALLOCATE THIS STUFF
	SDL_Surface *_aabbdebugsurface =
		SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
	SDL_FillRect(_aabbdebugsurface, NULL,
		     SDL_MapRGBA(_aabbdebugsurface->format, 0, 255, 0, 125));
	SDL_Texture *aabbDebugTexture =
		SDL_CreateTextureFromSurface(renderer, _aabbdebugsurface);


	resourceRegistry->window = window;
	resourceRegistry->renderer = renderer;
	resourceRegistry->resources.textures.testTexture = testTexture;
	resourceRegistry->resources.textures.aabbDebugTexture =
		aabbDebugTexture;
	resourceRegistry->resources.textures.planet1 = planet1;
	resourceRegistry->resources.textures.planet2 = planet2;
	resourceRegistry->resources.textures.planet3 = planet3;
	resourceRegistry->resources.textures.planet4 = planet4;
}
