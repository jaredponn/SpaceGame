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
	SDL_DestroyRenderer(registry->cRenderer);
	registry->cRenderer = NULL;
	SDL_DestroyWindow(registry->cWindow);
	registry->cWindow = NULL;

	// destroying the textures
	SDL_DestroyTexture(registry->cResources.cTextures.aabbDebugTexture);
	registry->cResources.cTextures.aabbDebugTexture = NULL;
	SDL_DestroyTexture(registry->cResources.cTextures.testTexture);
	registry->cResources.cTextures.testTexture = NULL;
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


	resourceRegistry->cWindow = window;
	resourceRegistry->cRenderer = renderer;
	resourceRegistry->cResources.cTextures.testTexture = testTexture;
	resourceRegistry->cResources.cTextures.aabbDebugTexture =
		aabbDebugTexture;
	resourceRegistry->cResources.cTextures.planet1 = planet1;
	resourceRegistry->cResources.cTextures.planet2 = planet2;
	resourceRegistry->cResources.cTextures.planet3 = planet3;
	resourceRegistry->cResources.cTextures.planet4 = planet4;
}
