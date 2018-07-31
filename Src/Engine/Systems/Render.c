#include "Render.h"
#include "Src/Engine/Components/Appearance.h"
// -----------------------------------------
//    Local functio declarations
// -----------------------------------------

// renders an appearance. Essentially a wrapper for SDL_RenderCopyEx, but
// assumes that we do not wish to flip to change the center of the object, nor
// flip it.
static void renderCopyAppearance(SDL_Renderer *, const struct Appearance *,
				 const struct EXS_GameCamera *);

static SDL_Rect convertSdlRectToScreenRect(const SDL_Rect *,
					   const struct EXS_GameCamera *);

// -----------------------------------------
//    Public function implementations
// -----------------------------------------

void SYS_renderCopy(SDL_Renderer *renderer,
		    const struct AppearanceManager *appearanceManager,
		    const struct EXS_GameCamera *gameCamera)
{
	const struct AppearanceVector *appVec_p =
		AppearanceManager_get_packed_data(appearanceManager);

	size_t vecLength = AppearanceVector_size(appVec_p);

	for (size_t i = 0; i < vecLength; ++i) {
		renderCopyAppearance(renderer,
				     AppearanceVector_get_p(appVec_p, i),
				     gameCamera);
	}
}

void SYS_renderDebugRectAabb(SDL_Renderer *renderer, SDL_Texture *debugTexture,
			     const void *rectAabbManager,
			     struct EXS_GameCamera *gameCamera)
{
	const struct RectAabbVector *rectAabbVec =
		RectAabbManager_get_packed_data(rectAabbManager);

	size_t size = RectAabbVector_size(rectAabbVec);

	struct RectAabb tmp;
	SDL_Rect tmpsdlrect;
	struct V2 lengths;

	for (size_t i = 0; i < size; ++i) {
		tmp = RectAabbVector_get(rectAabbVec, i);
		lengths = V2_sub(&tmp.pMax, &tmp.pMin);
		tmpsdlrect =
			convertSdlRectToScreenRect(&(SDL_Rect){.x = tmp.pMin.x,
							       .y = tmp.pMin.y,
							       .w = lengths.x,
							       .h = lengths.y},
						   gameCamera);
		SDL_RenderCopy(renderer, debugTexture, NULL, &tmpsdlrect);
	}
}

// -----------------------------------------
//    Local function implementations
// -----------------------------------------

static void renderCopyAppearance(SDL_Renderer *renderer,
				 const struct Appearance *appearance,
				 const struct EXS_GameCamera *gameCamera)
{
	// converting it from world corridantes to screen coordiantes
	SDL_Rect screenSdlRect =
		convertSdlRectToScreenRect(&appearance->dstrect, gameCamera);

	SDL_RenderCopy(renderer, appearance->texture, &appearance->srcrect,
		       &screenSdlRect);
}

static SDL_Rect
convertSdlRectToScreenRect(const SDL_Rect *sdlRect,
			   const struct EXS_GameCamera *gameCamera)
{

	return CPT_subtractSdlRectPosition(sdlRect,
					   &gameCamera->camera_position);
}
