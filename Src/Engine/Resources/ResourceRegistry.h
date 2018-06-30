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
        SDL_Texture* testTexture;
};

// Resources
struct ECS_Resources {
        struct ECS_Textures cTextures;
};

// all rendererer related things
struct ECS_ResourceRegistry {
        SDL_Window* cWindow;
        SDL_Renderer* cRenderer;
        struct ECS_Resources cResources;
};
