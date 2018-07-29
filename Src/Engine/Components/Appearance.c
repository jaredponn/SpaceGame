#include "Appearance.h"

// -----------------------------------------
//    Internal declarations
// -----------------------------------------

static Position position_round(const Position *const val);
// -----------------------------------------
//    Function implementations
// -----------------------------------------

void CPT_setSdlRectPosition(SDL_Rect *rect, const Position *const pos)
{
	Position roundedPos = position_round(pos);

	int nx = roundedPos.x;
	int ny = roundedPos.y;

	rect->x = nx;
	rect->y = ny;
}

void CPT_modifySdlRectPosition(SDL_Rect *rect, const Position *const pos)
{
	Position roundedPos = position_round(pos);

	int roundedx = roundedPos.x;
	int roundedy = roundedPos.y;

	rect->x += roundedx;
	rect->y += roundedy;
}

SDL_Rect CPT_addSdlRectPosition(const SDL_Rect *rect, const struct V2 *vec)
{
	return (SDL_Rect){.x = rect->x + vec->x,
			  .y = rect->y + vec->y,
			  .w = rect->w,
			  .h = rect->h};
}
SDL_Rect CPT_subtractSdlRectPosition(const SDL_Rect *rect, const struct V2 *vec)
{

	return (SDL_Rect){.x = rect->x - vec->x,
			  .y = rect->y - vec->y,
			  .w = rect->w,
			  .h = rect->h};
}


// internals
static Position position_round(const Position *const val)
{
	return (Position){.x = (int)val->x, .y = (int)val->y};
}
