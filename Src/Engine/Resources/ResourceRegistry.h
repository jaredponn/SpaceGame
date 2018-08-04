#pragma once

#include <SDL2/SDL.h>
#include "../Components/Aabb.h"
#include "../Components/Appearance.h"
#include "../Components/Entity.h"
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

	SDL_Texture *solar_station;
	SDL_Texture *solar_station_transparent;

	SDL_Texture *planet2;
	SDL_Texture *planet3;
	SDL_Texture *planet4;
};

// sound
struct RSC_Sound {
};

struct RSC_StationConfig {
	enum CPT_Entity entity;
	struct Appearance range_appearance;
	struct Appearance transparent_appearance;
	struct Appearance appearance;
	unsigned int cost;
	float w; /**< width */
	float h; /**< height */

	union {
		struct CircAabb circ_aabb;
		struct RectAabb rect_aabb;
	};
};

// game objects
struct RSC_GameObjects {
	struct RSC_StationConfig solar_station;
};


// Resources
struct RSC_Resources {
	struct RSC_Textures textures;
	struct RSC_Sound sound;
};

// accumalation of where to find all the various game resources. Sort of like
// Haskell lenses to focus on specific parts
// TODO why did i prefix this with ecs....
struct RSC_ResourceRegistry {
	SDL_Window *window;
	SDL_Renderer *renderer;
	struct RSC_Resources resources;

	struct RSC_GameObjects game_objects;
};

// -----------------------------------------
//    Procedures
// -----------------------------------------

// loads the resource registry with a renderer, window, and textures
void RSC_loadInitResources(struct RSC_ResourceRegistry *);

// clears and deallocates all resources in the registry
void RSC_destroyRegistry(struct RSC_ResourceRegistry *);
