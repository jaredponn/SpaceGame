#include "Appearance.h"

// -----------------------------------------
//    Macros
// -----------------------------------------
VECTOR_DEFINE(Appearance, Appearance)
COMPONENT_MANAGER_DEFINE(Appearance, Appearance)

// -----------------------------------------
//    Internal declarations
// -----------------------------------------

static Position position_round(const Position* const val);
// -----------------------------------------
//    Function implementations
// -----------------------------------------

void CPT_setSdlRectPosition(SDL_Rect* rect, const Position* const pos) {
        Position roundedPos = position_round(pos);

        int nx = roundedPos.x;
        int ny = roundedPos.y;

        rect->x = nx;
        rect->y = ny;
}

void CPT_modifySdlRectPosition(SDL_Rect* rect, const Position* const pos) {
        Position roundedPos = position_round(pos);

        int roundedx = roundedPos.x;
        int roundedy = roundedPos.y;

        rect->x += roundedx;
        rect->y += roundedy;
}

// internals
static Position position_round(const Position* const val) {
        return (Position){.x = (int)val->x, .y = (int)val->y};
}
