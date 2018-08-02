#pragma once
#include "Src/Engine/Components/Components.h"
#include "../ExtraState/EngineExtraState.h"

// -----------------------------------------
//    Procedures
// -----------------------------------------

// TODO ADD THE CAMERAPOSITION TO AFFECT THIS

// renders everythang formating in the Appearance Component
void SYS_renderCopy(SDL_Renderer *renderer,
		    const struct AppearanceManager *appearanceManager,
		    const struct EXS_GameCamera *);

// for rendering any RectAabb manager
void SYS_renderDebugRectAabb(SDL_Renderer *renderer,
			     const struct RectAabbManager *rectAabbManager,
			     struct EXS_GameCamera *, Uint8 r, Uint8 g, Uint8 b,
			     Uint8 a);

// for rendering the hitbox of any circ aabb
void SYS_renderDebugCircAabb(SDL_Renderer *renderer,
			     const struct CircAabbManager *rectAabbManager,
			     struct EXS_GameCamera *, Uint8 r, Uint8 g, Uint8 b,
			     Uint8 a);
