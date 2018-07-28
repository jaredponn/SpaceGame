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

#define CREATE_RECTAABB(prefix)                                                \
	/*RectAabb - used for detecting collisions of rectangles*/             \
	typedef struct prefix##RectAabb {                                      \
		struct V2 pMin;                                                \
		struct V2 pMax;                                                \
	} prefix##RectAabb;

#define CREATE_CIRCAABB(prefix)                                                \
	/*CircAabb - used for detecting collisions of circles*/                \
	typedef struct prefix##CircAabb {                                      \
		struct V2 center;                                              \
		float radius;                                                  \
	} prefix##CircAabb;

#define CREATE_SEGAABB(prefix)                                                 \
	/*SegAabb - used for detecting collisions of a line segment*/          \
	typedef struct prefix##SegAabb {                                       \
		struct V2 pMin;                                                \
		struct V2 pMax;                                                \
	} prefix##SegAabb;

// -----------------------------------------
//    Creating the default Aabb types
// -----------------------------------------
CREATE_RECTAABB()
CREATE_CIRCAABB()

// -----------------------------------------
//    Defining the sepcialized types for the CPT_Componeents
// -----------------------------------------
CREATE_RECTAABB(A)
CREATE_RECTAABB(B)

// assertions
_Static_assert(sizeof(RectAabb) == sizeof(ARectAabb),
	       "error - aabb data types are not the same size");
_Static_assert(sizeof(RectAabb) == sizeof(BRectAabb),
	       "error - aabb data types are not the same size");
// -----------------------------------------
//    Creating the defaul AABB managers that everything will cast to
// -----------------------------------------

VECTOR_DECLARE(RectAabb, RectAabb)
COMPONENT_MANAGER_DECLARE(RectAabb, RectAabb, RectAabb)

VECTOR_DECLARE(CircAabb, CircAabb)
COMPONENT_MANAGER_DECLARE(CircAabb, CircAabb, CircAabb)

// -----------------------------------------
//    Hit test procedures
// -----------------------------------------

// returns true if the the RectAabbs are overlapping
bool CPT_hitTestRectAabb(const RectAabb *, const RectAabb *);

// returns true if the point is within the RectAabb
bool CPT_hitTestPointRectAabb(const struct V2 *, const RectAabb *);

// returns true if the the RectAabbs are overlapping
bool CPT_hitTestCircAabb(const CircAabb *, const CircAabb *);

// returns true if th epoint is within the circle
bool CPT_hitTestPointCircAabb(const struct V2 *, const CircAabb *);

// returns true if the a circle Aabb and Rect aabb areoverlapping
// TODO actually not entirely sure how to go about writinh this
bool CPT_hitTestCircRectAabb(const CircAabb *, const RectAabb *);
