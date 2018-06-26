#pragma once

#include "Lib/GenericFreeList.h"
#include "Lib/GenericStack.h"
#include "Lib/GenericVector.h"

// stack
STACK_DECLARE(int, i)

// vector
VECTOR_DECLARE(int, i)

// freelist
struct FL_int {
        int myData;
        size_t next_free_index;
};

VECTOR_DECLARE(struct FL_int, FL_int)

FREELIST_DECLARE(struct FL_int, FL_int)
