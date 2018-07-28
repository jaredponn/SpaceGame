#include "Render.h"
#include "Src/Engine/Components/Appearance.h"
// -----------------------------------------
//    Local functio declarations
// -----------------------------------------

// renders an appearance. Essentially a wrapper for SDL_RenderCopyEx, but
// assumes that we do not wish to flip to change the center of the object, nor
// flip it.
static void renderCopyAppearance(SDL_Renderer *, const Appearance *);

// -----------------------------------------
//    Public function implementations
// -----------------------------------------

void SYS_renderCopy(SDL_Renderer *renderer,
		    const struct AppearanceManager *appearanceManager)
{
	const struct AppearanceVector *appVec_p =
		AppearanceManager_get_packed_data(appearanceManager);

	size_t size = AppearanceVector_size(appVec_p);

	for (size_t i = 0; i < size; ++i) {
		renderCopyAppearance(renderer,
				     AppearanceVector_get_p(appVec_p, i));
	}
}

void SYS_renderDebugRectAabb(SDL_Renderer *renderer, SDL_Texture *debugTexture,
			     const void *rectAabbManager)
{
	const struct RectAabbVector *rectAabbVec =
		RectAabbManager_get_packed_data(rectAabbManager);

	size_t size = RectAabbVector_size(rectAabbVec);

	RectAabb tmp;
	struct V2 lengths;

	for (size_t i = 0; i < size; ++i) {
		tmp = RectAabbVector_get(rectAabbVec, i);
		lengths = V2_sub(&tmp.pMax, &tmp.pMin);
		SDL_RenderCopy(renderer, debugTexture, NULL,
			       &(SDL_Rect){.x = tmp.pMin.x,
					   .y = tmp.pMin.y,
					   .w = lengths.x,
					   .h = lengths.y});
	}
}

// -----------------------------------------
//    Local function implementations
// -----------------------------------------

static void renderCopyAppearance(SDL_Renderer *renderer,
				 const Appearance *appearance)
{
	SDL_RenderCopyEx(renderer, appearance->texture, &appearance->srcrect,
			 &appearance->dstrect, appearance->angle, NULL,
			 SDL_FLIP_NONE);
}
