#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "Lib/GenericComponentManager.h"
#include "Lib/V2.h"
// -----------------------------------------
//    Data for Aabbs
// -----------------------------------------

// useful links:
// https://jaredponn.github.io/2018/06/07/Write-Me-A-FlappyBird-In-Haskell.html
// https://developer.mozilla.org/kab/docs/Games/Techniques/2D_collision_detection

// declares the default Rect and Circle Aabb which will becasted tofor every
// type

/*RectAabb - used for detecting collisions of rectangles*/
typedef struct RectAabb {
        struct V2 pMin;
        struct V2 pMax;
} RectAabb;

/*CircAabb - used for detecting collisions of circles*/
typedef struct CircAabb {
        struct V2 center;
        float radius;
} CircAabb;

/*SegAabb - used for detecting collisions of a line segment*/
typedef struct SegAabb {
        struct V2 pMin;
        struct V2 pMax;
} SegAabb;

// -----------------------------------------
//    final aabb type thats super inefficent, but less complicated and easier to
//    understand and implement for plebians
// -----------------------------------------
typedef enum CPT_AabbType { yRECT_AABB, CIRC_AABB, SEG_AABB } CPT_AabbType;
typedef enum CPT_CollisionLayers {
        et,
} CPT_CollisionLayers;

typedef struct Aabb {
        uint8_t aabbType : 4;
        uint8_t collisionLayer : 4;
        union {
                RectAabb rectAabb;
                CircAabb circAabb;
                SegAabb segAabb;
        };
} Aabb;

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
