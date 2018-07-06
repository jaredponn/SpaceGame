#pragma once

#include <SDL2/SDL.h>
#include "Lib/GenericComponentManager.h"
#include "Lib/GenericVector.h"
#include "Position.h"

typedef struct Appearance {
        SDL_Texture* texture;
        SDL_Rect srcrect;  // source rectangle
        SDL_Rect dstrect;  // destination rectangle
} Appearance;

VECTOR_DECLARE(Appearance, Appearance)
COMPONENT_MANAGER_DECLARE(Appearance, Appearance)

// changes the position of the SDL_Rect, and modifies the width and height so
// that it remains the same relative to the position
void CPT_modifySdlRectPosition(SDL_Rect*, const Position);
