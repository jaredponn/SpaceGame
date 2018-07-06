#include "Appearance.h"
#include <math.h>

VECTOR_DEFINE(Appearance, Appearance)
COMPONENT_MANAGER_DEFINE(Appearance, Appearance)

void CPT_modifySdlRectPosition(SDL_Rect* rect, const Position pos) {
        int nx = round(pos.x);
        int ny = round(pos.y);

        rect->w = rect->w + nx;
        rect->h = rect->h + ny;
        rect->x = nx;
        rect->y = ny;
}
