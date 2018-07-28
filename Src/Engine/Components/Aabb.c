#include "Aabb.h"

// -----------------------------------------
//    macros
// -----------------------------------------

// macro to make squaring a number a little easier
#define SQUARE(x) (((x)) * ((x)))

// -----------------------------------------
//    function implementations
// -----------------------------------------

bool CPT_hitTestRectAabb(const RectAabb *a, const RectAabb *b)
{
	return (a->pMin.x <= b->pMax.x && a->pMax.x >= b->pMin.x)
	       && (a->pMin.y <= b->pMax.y && a->pMax.y >= b->pMin.y);
}

bool CPT_hitTestPointRectAabb(const struct V2 *pt, const RectAabb *rect)
{
	return (pt->x >= rect->pMin.x && pt->x <= rect->pMax.x)
	       && (pt->y >= rect->pMin.y && pt->y <= rect->pMax.y);
}

// https://math.stackexchange.com/questions/198764/how-to-know-if-a-point-is-inside-a-circle
bool CPT_hitTestPointCircAabb(const struct V2 *pt, const CircAabb *circ)
{
	return SQUARE(SQUARE(pt->x - circ->center.x)
		      + SQUARE(pt->y - circ->center.y))
	       <= SQUARE(circ->radius);
}

// http://cgp.wikidot.com/circle-to-circle-collision-detection
bool CPT_hitTestCircAabb(const CircAabb *a, const CircAabb *b)
{
	float dx = a->center.x - b->center.x;
	float dy = a->center.y - b->center.y;

	float radii = a->radius + b->radius;

	return (SQUARE(dx) + SQUARE(dy)) < SQUARE(radii);
}

// -----------------------------------------
//    Macro definitinos
// -----------------------------------------

VECTOR_DEFINE(RectAabb, RectAabb)
COMPONENT_MANAGER_DEFINE(RectAabb, RectAabb, RectAabb)

VECTOR_DEFINE(CircAabb, CircAabb)
COMPONENT_MANAGER_DEFINE(CircAabb, CircAabb, CircAabb)
