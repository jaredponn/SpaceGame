#pragma once

#include <SDL2/SDL.h>
#include "Lib/GenericComponentManager.h"
#include "Lib/GenericVector.h"
#include "Movement.h"

typedef struct Appearance {
        SDL_Texture* texture;
        SDL_Rect srcrect;  // source rectangle
        SDL_Rect dstrect;  // destination rectangle
        double angle;      // angle to rotate the texture
} Appearance;

// sets the position of the SDL_Rect
void CPT_setSdlRectPosition(SDL_Rect*, const Position* const);

// adds the position to the SDL_Rect
void CPT_modifySdlRectPosition(SDL_Rect* rect, const Position* const pos);
