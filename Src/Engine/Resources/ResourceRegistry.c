#include "ResourceRegistry.h"
#include <SDL2/SDL_image.h>
#include "LoadResources.h"

// clang-format off
#define EXTRAS_PATH "/home/jared/Programs/SpaceGame/Extras"
// clang-format on

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

void ECS_destroyRegistry(struct ECS_ResourceRegistry *registry) {
        SDL_DestroyRenderer(registry->cRenderer);
        registry->cRenderer = NULL;
        SDL_DestroyWindow(registry->cWindow);
        registry->cWindow = NULL;

        // destroying the textures
        SDL_DestroyTexture(registry->cResources.cTextures.testTexture);
        registry->cResources.cTextures.testTexture = NULL;
}

void ECS_loadInitResources(struct ECS_ResourceRegistry *resourceRegistry) {
        SDL_Window *window = RSC_createInitWindow(
            "Space Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

        SDL_Renderer *renderer =
            RSC_createInitRenderer(window, SDL_RENDERER_ACCELERATED);

        // TODO add proper error handling
        SDL_Texture *testTexture =
            RSC_loadImage(renderer, EXTRAS_PATH "/Images/bg.png");

        resourceRegistry->cWindow = window;
        resourceRegistry->cRenderer = renderer;
        resourceRegistry->cResources.cTextures.testTexture = testTexture;
}
