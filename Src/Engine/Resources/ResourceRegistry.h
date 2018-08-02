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
struct ECS_Textures {
	SDL_Texture *testTexture;
	SDL_Texture *aabbDebugTexture;

	SDL_Texture *planet1;
	SDL_Texture *planet2;
	SDL_Texture *planet3;
	SDL_Texture *planet4;
};

// Resources
struct ECS_Resources {
	struct ECS_Textures cTextures;
};

// accumalation of where to find all the various game resources. Sort of like
// Haskell lenses to focus on specific parts
struct ECS_ResourceRegistry {
	SDL_Window *cWindow;
	SDL_Renderer *cRenderer;
	struct ECS_Resources cResources;
};

// -----------------------------------------
//    Procedures
// -----------------------------------------

// loads the resource registry with a renderer, window, and textures
void ECS_loadInitResources(struct ECS_ResourceRegistry *);

// clears and deallocates all resources in the registry
void ECS_destroyRegistry(struct ECS_ResourceRegistry *);
