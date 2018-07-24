#pragma once

#include "Lib/GenericComponentManager.h"
#include "Lib/GenericFreeList.h"
#include "Lib/GenericPackedVector.h"
#include "Lib/GenericStack.h"
#include "Lib/GenericVector.h"

// stack
STACK_DECLARE(int, i)

// vector
VECTOR_DECLARE(int, int)

// freelist
struct FLInt {
        int myData;
        size_t next_free_index;
};
VECTOR_DECLARE(struct FLInt, FLInt)
FREELIST_DECLARE(struct FLInt, FLInt, FLInt)

// packed vector
PACKEDVECTOR_DECLARE(int, int, int)
