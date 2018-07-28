#pragma once

#include "GenericFreeList.h"
#include "GenericVector.h"
#include "stdbool.h"

/**
 * Contains declarations for a free list that contains an extra bool to mark the
 * "free" and "used" indexes within a system. Mainly used to find the unused
 * indexes of an array in a system.
 */

typedef struct MarkedIndex {
	bool is_used;		/**< is true if the index is used/vacant */
	size_t next_free_index; /**< interanls for the free list */
} MarkedIndex;

VECTOR_DECLARE(MarkedIndex, MarkedIndex)
FREELIST_DECLARE(MarkedIndex, Marked, MarkedIndex)

// updates the index so the current free index points to a new free elemnet
void MarkedFreeList_update_index(struct MarkedFreeList *);

// marks an index as free. WARNING: no bounds checking
void MarkedFreeList_mark_index_as_free(struct MarkedFreeList *, size_t);

// marks an index as used. WARNING: no bounds checking
void MarkedFreeList_mark_index_as_used(struct MarkedFreeList *, size_t);

// returns true if the index is free
bool MarkedFreeList_is_index_free(struct MarkedFreeList *, size_t);

// returns true if the index is used
bool MarkedFreeList_is_index_used(struct MarkedFreeList *, size_t);
