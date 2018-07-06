#pragma once

#include "Lib/GenericVector.h"
#include "Lib/sizet_Vector.h"
#include "SDL2/SDL.h"

typedef struct Appearance {
        SDL_Texture* texture;
        SDL_Rect srcrect;  // source rectangle
        SDL_Rect dstrect;  // destination rectangle
} Appearance;

VECTOR_DECLARE(Appearance, Appearance)

struct AppearanceManager {
        struct sizet_Vector id;
        struct Appearance_Vector appearances;
};

// initilizes apperance manager
void initAppearanceManager(struct AppearanceManager* appearancesManager,
                           size_t capacity);
