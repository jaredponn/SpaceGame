#pragma once
#include <stdbool.h>
#include "Lib/V2.h"

// -----------------------------------------
//    Macros for generating Aabbs
// -----------------------------------------

#define DECLARE_RECTAABB_LAYER(layername)                          \
        /*Types*/                                                  \
        /*RectAabb - used for detecting collisions of rectangles*/ \
        typedef struct RectAabb##layername {                       \
                struct V2 pMin;                                    \
                struct V2 pMax;                                    \
        } RectAabb##layername;

#define DECLARE_CIRCAABB_LAYER(layername)                       \
        /*Types*/                                               \
        /*CircAabb - used for detecting collisions of circles*/ \
        typedef struct CircAabb##layername {                    \
                struct V2 center;                               \
                float radius;                                   \
        } CircAabb##layername;

#define DECLARE_SEGAABB_LAYER(layername)                              \
        /*Types*/                                                     \
        /*SegAabb - used for detecting collisions of a line segment*/ \
        typedef struct SegAabb##layername {                           \
                struct V2 pMin;                                       \
                struct V2 pMax;                                       \
        } SegAabb##layername;

// -----------------------------------------
//    Data for Aabbs
// -----------------------------------------

// useful links:
// https://jaredponn.github.io/2018/06/07/Write-Me-A-FlappyBird-In-Haskell.html
// https://developer.mozilla.org/kab/docs/Games/Techniques/2D_collision_detection

// declares the default Rect and Circle Aabb which will becasted tofor every
// type
DECLARE_RECTAABB_LAYER()
DECLARE_CIRCAABB_LAYER()
DECLARE_SEGAABB_LAYER()

// declaring additional layers
DECLARE_RECTAABB_LAYER(0)

// -----------------------------------------
//    Hit test procedures
// -----------------------------------------

// returns true if the the RectAabbs are overlapping
bool CPT_hitTestRectAabb(const RectAabb*, const RectAabb*);

// returns true if the point is within the RectAabb
bool CPT_hitTestPointRectAabb(const struct V2*, const RectAabb*);

// returns true if the the RectAabbs are overlapping
bool CPT_hitTestCircAabb(const CircAabb*, const CircAabb*);

// returns true if th epoint is within the circle
bool CPT_hitTestPointCircAabb(const struct V2*, const CircAabb*);

// returns true if the a circle Aabb and Rect aabb areoverlapping
// TODO actually not entirely sure how to go about writinh this
bool CPT_hitTestCircRectAabb(const CircAabb*, const RectAabb*);
