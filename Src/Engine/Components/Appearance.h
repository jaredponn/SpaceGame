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

// sets the position of the SDL_Rect
void CPT_setSdlRectPosition(SDL_Rect*, const Position);

// adds the position to the SDL_Rect
void CPT_modifySdlRectPosition(SDL_Rect* rect, const Position pos);
