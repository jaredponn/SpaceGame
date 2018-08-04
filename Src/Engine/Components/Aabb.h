#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "Lib/GenericComponentManager.h"
#include "Lib/V2.h"
// -----------------------------------------
//    Macros for the data to create Aabbs
// -----------------------------------------

// useful links:
// https://jaredponn.github.io/2018/06/07/Write-Me-A-FlappyBird-In-Haskell.html
// https://developer.mozilla.org/kab/docs/Games/Techniques/2D_collision_detection

/*RectAabb - used for detecting collisions of rectangles*/
struct RectAabb {
	struct V2 pMin;
	struct V2 pMax;
};

/*CircAabb - used for detecting collisions of circles*/
struct CircAabb {
	struct V2 center;
	float radius;
};

/*SegAabb - used for detecting collisions of a line segment*/
struct SegAabb {
	struct V2 pMin;
	struct V2 pMax;
};


VECTOR_DECLARE(struct RectAabb, RectAabb)
COMPONENT_MANAGER_DECLARE(struct RectAabb, RectAabb, RectAabb)

VECTOR_DECLARE(struct CircAabb, CircAabb)
COMPONENT_MANAGER_DECLARE(struct CircAabb, CircAabb, CircAabb)

// -----------------------------------------
//    Hit test procedures
// -----------------------------------------

// returns true if the the RectAabbs are overlapping
bool CPT_hitTestRectAabb(const struct RectAabb *, const struct RectAabb *);

// returns true if the point is within the RectAabb
bool CPT_hitTestPointRectAabb(const struct V2 *, const struct RectAabb *);

// returns true if the the RectAabbs are overlapping
bool CPT_hitTestCircAabb(const struct CircAabb *, const struct CircAabb *);

// returns true if th epoint is within the circle
bool CPT_hitTestPointCircAabb(const struct V2 *, const struct CircAabb *);

// returns true if the a circle Aabb and Rect aabb areoverlapping
bool CPT_hitTestCircRectAabb(const struct CircAabb *, const struct RectAabb *);

// creates a CircAabb at position (0,0) with the given radius
struct CircAabb CPT_createCircAabb(float r);

// gets the offset for the position, so the center of the circle is on the mouse
struct V2 CPT_getCircOffset(float w, float h);
