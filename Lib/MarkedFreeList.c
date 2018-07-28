#include "MarkedFreeList.h"

VECTOR_DEFINE(MarkedIndex, MarkedIndex)
FREELIST_DEFINE(MarkedIndex, Marked, MarkedIndex)

// -----------------------------------------
//    private func
// -----------------------------------------

// sets the given index's "is_free" paramater. WARNING: Does not do bounds
// checking
static inline void MarkedFreeList_mark_index_as(struct MarkedFreeList *, size_t,
						bool);

// -----------------------------------------
//    public
// -----------------------------------------

void MarkedFreeList_update_index(struct MarkedFreeList *markedfreelist)
{
	size_t curFreeIndex =
		MarkedFreeList_get_curr_free_index(markedfreelist);
	struct MarkedIndex tmp =
		MarkedFreeList_get(markedfreelist, curFreeIndex);
	tmp.is_used = true;


	(void)MarkedFreeList_add(markedfreelist, tmp);
}


void MarkedFreeList_mark_index_as_free(struct MarkedFreeList *markedfreelist,
				       size_t index)
{
	MarkedFreeList_mark_index_as(markedfreelist, index, false);
}

void MarkedFreeList_mark_index_as_used(struct MarkedFreeList *markedfreelist,
				       size_t index)
{
	MarkedFreeList_mark_index_as(markedfreelist, index, true);
}

bool MarkedFreeList_is_index_free(struct MarkedFreeList *markedfreelist,
				  size_t index)
{

	return !MarkedIndexVector_get(&markedfreelist->data, index).is_used;
}

bool MarkedFreeList_is_index_used(struct MarkedFreeList *markedfreelist,
				  size_t index)
{
	return MarkedIndexVector_get(&markedfreelist->data, index).is_used;
}

// -----------------------------------------
//    private funcs
// -----------------------------------------

static inline void
MarkedFreeList_mark_index_as(struct MarkedFreeList *markedfreelist,
			     size_t index, bool val)
{
	MarkedIndexVector_get_p(&markedfreelist->data, index)->is_used = val;
}
