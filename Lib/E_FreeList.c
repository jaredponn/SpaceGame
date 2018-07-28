#include "E_FreeList.h"

VECTOR_DEFINE(E, E)
FREELIST_DEFINE(E, E, E)

// 1 denotes is free
size_t isFree(E *n)
{
	return n->next_free_index & 1;
}

// 1 denotes is free
void invertIsFree(E *n)
{
	n->next_free_index = n->next_free_index ^ 1;
}

size_t getIndex(E *n)
{
	return n->next_free_index >> 1;
}

void setIndex(E *n, size_t val)
{
	n->next_free_index = (val << 1) | isFree(n);
}
