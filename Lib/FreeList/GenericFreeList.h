#pragma once

#include <stdlib.h>

#include "../Stack/SizeStack.h"
#undef TYPE
#undef TYPED

#include "../Util.h"
#undef TYPE
#undef TYPED

#include "../Vector/IntVector.h"
#undef TYPE
#undef TYPED

/**
 * Declarations for a generic free list structure
 */

// -----------------------------------------
//    Macros
// -----------------------------------------

// TODO

// -----------------------------------------
//    Types
// -----------------------------------------

struct FreeList;
struct FreeList {
        struct i_Vector data;
        struct size_t_Stack free_elements;
};

// -----------------------------------------
//    Procedures
// -----------------------------------------

void freelist_init(struct FreeList*);

// wrapper for vector_reserve. Should only be called after inititziatlino
void freelist_reserve(struct FreeList*, size_t);

// adds an element to the nearest spot on the structure
void freelist_add(struct FreeList*, int);

// gets an elment at an index
int freelist_get(struct FreeList*, size_t);

// removes an element at the given index. Appends it to the free_elements stack
void freelist_removeat(struct FreeList*, size_t);
