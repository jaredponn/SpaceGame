#include "ResourceRegistry.h"
#include <SDL2/SDL_image.h>

void ECS_destroyRegistry(struct ECS_ResourceRegistry* registry) {
        SDL_DestroyRenderer(registry->cRenderer);
        registry->cRenderer = NULL;
        SDL_DestroyWindow(registry->cWindow);
        registry->cWindow = NULL;

        // destroying the textures
        SDL_DestroyTexture(registry->cResources.cTextures.testTexture);
        registry->cResources.cTextures.testTexture = NULL;
}
