#include "Aabb.h"

// -----------------------------------------
//    macros
// -----------------------------------------

// macros to make the computations a bit easier
#define SQUARE(x) (((x)) * ((x)))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

// -----------------------------------------
//    function implementations
// -----------------------------------------

bool CPT_hitTestRectAabb(const struct RectAabb *a, const struct RectAabb *b)
{
	return (a->pMin.x <= b->pMax.x && a->pMax.x >= b->pMin.x)
	       && (a->pMin.y <= b->pMax.y && a->pMax.y >= b->pMin.y);
}

bool CPT_hitTestPointRectAabb(const struct V2 *pt, const struct RectAabb *rect)
{
	return (pt->x >= rect->pMin.x && pt->x <= rect->pMax.x)
	       && (pt->y >= rect->pMin.y && pt->y <= rect->pMax.y);
}

// https://math.stackexchange.com/questions/198764/how-to-know-if-a-point-is-inside-a-circle
bool CPT_hitTestPointCircAabb(const struct V2 *pt, const struct CircAabb *circ)
{
	return SQUARE(SQUARE(pt->x - circ->center.x)
		      + SQUARE(pt->y - circ->center.y))
	       <= SQUARE(circ->radius);
}

// http://cgp.wikidot.com/circle-to-circle-collision-detection
bool CPT_hitTestCircAabb(const struct CircAabb *a, const struct CircAabb *b)
{
	float dx = a->center.x - b->center.x;
	float dy = a->center.y - b->center.y;

	float radii = a->radius + b->radius;

	return (SQUARE(dx) + SQUARE(dy)) < SQUARE(radii);
}

// https://yal.cc/rectangle-circle-intersection-test/
bool CPT_hitTestCircRectAabb(const struct CircAabb *circ,
			     const struct RectAabb *rect)
{
	float radius = circ->radius;
	float dx = circ->center.x
		   - MAX(rect->pMin.x, MIN(circ->center.x, rect->pMax.x));
	float dy = circ->center.y
		   - MAX(rect->pMin.y, MIN(circ->center.y, rect->pMax.y));

	return (SQUARE(dx) + SQUARE(dy)) < SQUARE(radius);
}

// -----------------------------------------
//    Macro definitinos
// -----------------------------------------

VECTOR_DEFINE(struct RectAabb, RectAabb)
COMPONENT_MANAGER_DEFINE(struct RectAabb, RectAabb, RectAabb)

VECTOR_DEFINE(struct CircAabb, CircAabb)
COMPONENT_MANAGER_DEFINE(struct CircAabb, CircAabb, CircAabb)

#undef SQUARE
#undef MAX
#undef MIN
