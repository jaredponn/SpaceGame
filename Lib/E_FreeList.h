#pragma once

#include <stdlib.h>
#include "GenericFreeList.h"
#include "GenericVector.h"

/**
 * Declarations for an empty free list structure named E_FreeList. (E stands for
 * empty)
 */

struct FL_index;
struct FL_index {
        size_t next_free_index;
};

typedef struct FL_index E;

VECTOR_DECLARE(E, E)
FREELIST_DECLARE(E, E)
