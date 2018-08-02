#include "Render.h"
#include "Src/Engine/Components/Appearance.h"

#include <math.h>

#define PI 3.14159265358979323
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
			     const struct RectAabbManager *rectAabbManager,
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

void SYS_renderDebugCircAabb(SDL_Renderer *renderer,
			     const struct CircAabbManager *circAabbManager,
			     struct EXS_GameCamera *gameCamera)
{
	const struct CircAabbVector *circAabbVec =
		CircAabbManager_get_packed_data(circAabbManager);

	size_t vecLength = CircAabbVector_size(circAabbVec);

	// setting the dot color to red
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);

	// radius
	float radius;
	struct V2 tmp;

	// perimeter x/y coord
	struct V2 ptmp;

	for (size_t i = 0; i < vecLength; ++i) {
		radius = CircAabbVector_get(circAabbVec, i).radius;
		tmp.x = CircAabbVector_get(circAabbVec, i).center.x;
		tmp.y = CircAabbVector_get(circAabbVec, i).center.y;

		// rendering dots on the perimeter
		for (float j = 0; j < 2 * PI; j += 0.01) {
			ptmp.x = cosf(j) * radius + tmp.x
				 - gameCamera->camera_position.x;
			ptmp.y = sinf(j) * radius + tmp.y
				 - gameCamera->camera_position.y;

			SDL_RenderDrawPoint(renderer, ptmp.x, ptmp.y);
		}
	}
};
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
