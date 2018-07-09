#include "Engine.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

// clang-format off
#define _EXTRAS_PATH "/home/jared/Programs/SpaceGame/Extras"
// clang-format on

// -----------------------------------------
//    Constants
// -----------------------------------------
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// -----------------------------------------
//    Internal function declarations
// -----------------------------------------

// deletes the entity along with all of its componenets
void delete_entity(size_t index);

// -----------------------------------------
//    Procedures
// -----------------------------------------

void ECS_initLibraries() {
        RSC_initSDL(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
        RSC_initSDLImage(IMG_INIT_PNG);
}

void ECS_initComponents(struct ECS_Components *engine, size_t capacity) {
        Entity_manager_init(&engine->entity_manager, capacity);
        Position_manager_init(&engine->position_manager, capacity);
        Appearance_manager_init(&engine->appearance_manager, capacity);
}

void ECS_loadInitResources(struct ECS_ResourceRegistry *resourceRegistry) {
        SDL_Window *window = RSC_createInitWindow(
            "Space Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

        SDL_Renderer *renderer =
            RSC_createInitRenderer(window, SDL_RENDERER_ACCELERATED);

        // TODO add proper error handling
        SDL_Texture *testTexture =
            RSC_loadImage(renderer, _EXTRAS_PATH "/Images/bg.png");

        resourceRegistry->cWindow = window;
        resourceRegistry->cRenderer = renderer;
        resourceRegistry->cResources.cTextures.testTexture = testTexture;
}

void ECS_runEngine(struct ECS_Components *engineComponents,
                   struct ECS_ResourceRegistry *resourceRegistry) {
        while (1) {
                SDL_Event e;
                if (SDL_PollEvent(&e)) {
                        if (e.type == SDL_QUIT) {
                                break;
                        }
                }

                SDL_RenderClear(resourceRegistry->cRenderer);
                SDL_RenderCopy(
                    resourceRegistry->cRenderer,
                    resourceRegistry->cResources.cTextures.testTexture, NULL,
                    NULL);
                SDL_RenderPresent(resourceRegistry->cRenderer);
        }
}

void ECS_quitLibraries() {
        SDL_Quit();
        IMG_Quit();
}
// -----------------------------------------
//    Internal functions' definitions
// -----------------------------------------
