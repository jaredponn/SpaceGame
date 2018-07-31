#pragma once

#include <SDL2/SDL.h>
#include "Lib/GenericComponentManager.h"
#include "Lib/GenericVector.h"
#include "Movement.h"
#include "Lib/V2.h"

struct Appearance {
	SDL_Texture *texture;
	SDL_Rect srcrect; // source rectangle
	SDL_Rect dstrect; // destination rectangle
} Appearance;

struct RotatedAppearance {
	SDL_Texture *texture;
	SDL_Rect srcrect; // source rectangle
	SDL_Rect dstrect; // destination rectangle
	double angle;     // angle to rotate the texture
} RotatedAppearance;

// sets the position of the SDL_Rect
void CPT_setSdlRectPosition(SDL_Rect *, const Position *const);

// adds the position to the SDL_Rect
void CPT_modifySdlRectPosition(SDL_Rect *rect, const Position *const pos);

// adds like: apperaance + pos
SDL_Rect CPT_addSdlRectPosition(const SDL_Rect *rect, const struct V2 *vec);
// subtracts like: apperaance - pos
SDL_Rect CPT_subtractSdlRectPosition(const SDL_Rect *rect,
				     const struct V2 *vec);

VECTOR_DECLARE(struct Appearance, Appearance)
COMPONENT_MANAGER_DECLARE(struct Appearance, Appearance, Appearance)

VECTOR_DECLARE(struct RotatedAppearance, RotatedAppearance)
COMPONENT_MANAGER_DECLARE(struct RotatedAppearance, RotatedAppearance,
			  RotatedAppearance)
