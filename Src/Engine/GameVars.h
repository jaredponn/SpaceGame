#pragma once

#include "Lib/GenericFreeList.h"
#include "Lib/GenericStack.h"
#include "Lib/GenericVector.h"

// -----------------------------------------
//    Entity
// -----------------------------------------

typedef int Entity;

STACK_DECLARE(size_t, size)
VECTOR_DECLARE(Entity, ent)
FREELIST_DECLARE(Entity, ent)

enum Components {
        COMPONENT_POSITION = 1 << 0,
        COMPONENT_APPEARANCE = 1 << 1

};
// -----------------------------------------
//    Vectors to Components
// -----------------------------------------
typedef size_t ID;
VECTOR_DECLARE(ID, id)

// -----------------------------------------
//    Components
// -----------------------------------------
typedef struct Appearance {
        char* name;
} Appearance;

VECTOR_DECLARE(Appearance, app)

typedef struct Position {
        float x;
        float y;
} Position;

VECTOR_DECLARE(Position, pos)

struct whatthefuck {
        int a;
        int b;
        void* fuck;
};

struct World {
        struct ent_FreeList entities;
        struct id_Vector appearances;
        struct id_Vector positions;
};
