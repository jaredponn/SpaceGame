#include "ResourceRegistry.h"
#include <SDL2/SDL_image.h>
#include "LoadResources.h"

// clang-format off
#define EXTRAS_PATH "/home/jared/Programs/SpaceGame/Extras"
// clang-format on

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

void RSC_destroyRegistry(struct RSC_ResourceRegistry *registry)
{
	SDL_DestroyRenderer(registry->renderer);
	registry->renderer = NULL;
	SDL_DestroyWindow(registry->window);
	registry->window = NULL;

	// destroying the textures
	/** SDL_DestroyTexture(registry->resources.textures.aabbDebugTexture);
	 */
	/** registry->resources.textures.aabbDebugTexture = NULL; */
	/** SDL_DestroyTexture(registry->resources.textures.testTexture); */
	/** registry->resources.textures.testTexture = NULL; */
}

// loads an image with "NAME" and a transparentimage named "name_transparent"
// with opacity of "OPACITY"
#define LOAD_IMAGE_AND_TRANSPARENT(NAME, OPACITY, FILEPATH)                    \
	SDL_Texture *NAME = RSC_loadImage(renderer, FILEPATH);                 \
	SDL_Texture *NAME##_transparent = RSC_loadImage(renderer, FILEPATH);   \
	SDL_SetTextureAlphaMod(NAME##_transparent, OPACITY)

void RSC_loadInitResources(struct RSC_ResourceRegistry *resourceRegistry)
{
	SDL_Window *window = RSC_createInitWindow(
		"Space Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

	SDL_Renderer *renderer =
		RSC_createInitRenderer(window, SDL_RENDERER_ACCELERATED);

	// TODO add proper error handling

	// SOLARSTATION
	/** SDL_Texture *solar_station = RSC_loadImage( */
	/**         renderer, EXTRAS_PATH "/Images/500x500circ-01.png"); */
	/** SDL_Texture *solar_station_transparent = RSC_loadImage( */
	/**         renderer, EXTRAS_PATH "/Images/500x500circ-01.png"); */
	/** SDL_SetTextureAlphaMod(solar_station_transparent, 50); */

	LOAD_IMAGE_AND_TRANSPARENT(solar_station, 50,
				   EXTRAS_PATH "/Images/500x500circ-01.png");

	// LASER STATION
	LOAD_IMAGE_AND_TRANSPARENT(laser_station, 50,
				   EXTRAS_PATH "/Images/500x500circ-02.png");

	// missile station the fuck
	LOAD_IMAGE_AND_TRANSPARENT(missile_station, 50,
				   EXTRAS_PATH "/Images/500x500circ-03.png");
	// mine station
	LOAD_IMAGE_AND_TRANSPARENT(mine_station, 50,
				   EXTRAS_PATH "/Images/500x500circ-04.png");


	resourceRegistry->window = window;
	resourceRegistry->renderer = renderer;

	// solar station
	resourceRegistry->game_objects.solar_station.cost = 100;
	resourceRegistry->game_objects.solar_station.entity = CPT_SOLARSTATION;
	resourceRegistry->game_objects.solar_station.w = 100;
	resourceRegistry->game_objects.solar_station.h = 100;
	resourceRegistry->game_objects.solar_station.circ_aabb =
		CPT_createCircAabb(50);
	resourceRegistry->game_objects.solar_station
		.transparent_appearance = (struct Appearance){
		.texture = solar_station_transparent,
		.srcrect = (SDL_Rect){.x = 0, .y = 0, .w = 1042, .h = 1042},
		.dstrect = (SDL_Rect){.x = 0, .y = 0, .w = 100, .h = 100}};
	resourceRegistry->game_objects.solar_station
		.appearance = (struct Appearance){
		.texture = solar_station,
		.srcrect = (SDL_Rect){.x = 0, .y = 0, .w = 1042, .h = 1042},
		.dstrect = (SDL_Rect){.x = 0, .y = 0, .w = 100, .h = 100}};

	// laser station
	resourceRegistry->game_objects.laser_station.cost = 100;
	resourceRegistry->game_objects.laser_station.entity = CPT_LASERSTATION;
	resourceRegistry->game_objects.laser_station.w = 100;
	resourceRegistry->game_objects.laser_station.h = 100;
	resourceRegistry->game_objects.laser_station.circ_aabb =
		CPT_createCircAabb(50);
	resourceRegistry->game_objects.laser_station
		.transparent_appearance = (struct Appearance){
		.texture = laser_station,
		.srcrect = (SDL_Rect){.x = 0, .y = 0, .w = 1042, .h = 1042},
		.dstrect = (SDL_Rect){.x = 0, .y = 0, .w = 100, .h = 100}};
	resourceRegistry->game_objects.laser_station
		.appearance = (struct Appearance){
		.texture = laser_station,
		.srcrect = (SDL_Rect){.x = 0, .y = 0, .w = 1042, .h = 1042},
		.dstrect = (SDL_Rect){.x = 0, .y = 0, .w = 100, .h = 100}};

	// missile station
	resourceRegistry->game_objects.missile_station.cost = 100;
	resourceRegistry->game_objects.missile_station.entity =
		CPT_MISSILESTATION;
	resourceRegistry->game_objects.missile_station.w = 100;
	resourceRegistry->game_objects.missile_station.h = 100;
	resourceRegistry->game_objects.missile_station.circ_aabb =
		CPT_createCircAabb(50);
	resourceRegistry->game_objects.missile_station
		.transparent_appearance = (struct Appearance){
		.texture = missile_station,
		.srcrect = (SDL_Rect){.x = 0, .y = 0, .w = 1042, .h = 1042},
		.dstrect = (SDL_Rect){.x = 0, .y = 0, .w = 100, .h = 100}};
	resourceRegistry->game_objects.missile_station
		.appearance = (struct Appearance){
		.texture = missile_station,
		.srcrect = (SDL_Rect){.x = 0, .y = 0, .w = 1042, .h = 1042},
		.dstrect = (SDL_Rect){.x = 0, .y = 0, .w = 100, .h = 100}};

	// mine station
	resourceRegistry->game_objects.mine_station.cost = 100;
	resourceRegistry->game_objects.mine_station.entity = CPT_MINESTATION;
	resourceRegistry->game_objects.mine_station.w = 100;
	resourceRegistry->game_objects.mine_station.h = 100;
	resourceRegistry->game_objects.mine_station.circ_aabb =
		CPT_createCircAabb(50);
	resourceRegistry->game_objects.mine_station
		.transparent_appearance = (struct Appearance){
		.texture = mine_station,
		.srcrect = (SDL_Rect){.x = 0, .y = 0, .w = 1042, .h = 1042},
		.dstrect = (SDL_Rect){.x = 0, .y = 0, .w = 100, .h = 100}};
	resourceRegistry->game_objects.mine_station
		.appearance = (struct Appearance){
		.texture = mine_station,
		.srcrect = (SDL_Rect){.x = 0, .y = 0, .w = 1042, .h = 1042},
		.dstrect = (SDL_Rect){.x = 0, .y = 0, .w = 100, .h = 100}};
}
