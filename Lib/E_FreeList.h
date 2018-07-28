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

VECTOR_DECLARE(E, E) // declares vector of type E -> EVector
FREELIST_DECLARE(E, E, E)


// -----------------------------------------
//    Extra functionality to work with the E data type.
// -----------------------------------------
/** These functions can be used to mark whether that specific index is "free" or
 * "used", while keepig track of the next free index.
 */

// returns whether it is free or not
size_t isFree(E *n);

// inverses whether it is free or not (NOT)
void invertIsFree(E *n);

// gets the index
size_t getIndex(E *n);

// sets the index
void setIndex(E *n, size_t val);
