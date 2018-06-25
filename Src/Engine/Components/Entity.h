#pragma once

#include "Lib/GenericFreeList.h"
#include "Lib/GenericVector.h"

// -----------------------------------------
//    Entity
// -----------------------------------------

// bit shifted integer to keep track of which components the entity has
typedef unsigned int Entity;

struct FL_Entity;
struct FL_Entity {
        Entity entity;
        size_t next_free_index;
};

VECTOR_DECLARE(struct FL_Entity, FL_Entity)
FREELIST_DECLARE(struct FL_Entity, FL_Entity)

// -----------------------------------------
//    Componenets
// -----------------------------------------

typedef enum Components {
        COMPONENT_NONE = 1 << 0,
        COMPONENT_POSITION = 1 << 1,
        COMPONENT_APPEARANCE = 1 << 2

} Components;
