#pragma once

#include <SDL2/SDL.h>
// -----------------------------------------
//    Macros
// -----------------------------------------

// clang-format off
// clang-format on

// -----------------------------------------
//    Types
// -----------------------------------------

// textures
struct RSC_Textures {
	SDL_Texture *testTexture;
	SDL_Texture *aabbDebugTexture;

	SDL_Texture *planet1;
	SDL_Texture *planet2;
	SDL_Texture *planet3;
	SDL_Texture *planet4;
};

// Resources
struct RSC_Resources {
	struct RSC_Textures textures;
};

// accumalation of where to find all the various game resources. Sort of like
// Haskell lenses to focus on specific parts
// TODO why did i prefix this with ecs....
struct RSC_ResourceRegistry {
	SDL_Window *window;
	SDL_Renderer *renderer;
	struct RSC_Resources resources;
};

// -----------------------------------------
//    Procedures
// -----------------------------------------

// loads the resource registry with a renderer, window, and textures
void RSC_loadInitResources(struct RSC_ResourceRegistry *);

// clears and deallocates all resources in the registry
void RSC_destroyRegistry(struct RSC_ResourceRegistry *);
