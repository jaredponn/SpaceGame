#pragma once

#include "Lib/GenericFreeList.h"
#include "Lib/GenericVector.h"

// -----------------------------------------
//    Entity
// -----------------------------------------

// bit shifted integer corrosponding to the enum Componenets that keeps track of
// which Components the entity contains
typedef unsigned int Entity;
VECTOR_DECLARE(Entity, Entity)

struct FL_indices;
struct FL_indices {
        size_t next_free_index;
};

VECTOR_DECLARE(struct FL_indices, FL_indices)
FREELIST_DECLARE(struct FL_indices, FL_indices)

struct EntityManager;
struct EntityManager {
        struct Entity_Vector entities;
        struct FL_indices_FreeList free_elements;
};

// -----------------------------------------
//    Componenets
// -----------------------------------------

typedef enum Components {
        COMPONENT_NONE = 1 << 0,
        COMPONENT_POSITION = 1 << 1,
        COMPONENT_APPEARANCE = 1 << 2

} Components;
