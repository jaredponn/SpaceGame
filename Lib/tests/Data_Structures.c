#include "Data_Structures.h"

STACK_DEFINE(int, i)

VECTOR_DEFINE(int, i)

VECTOR_DEFINE(struct FL_int, FL_int)

FREELIST_DEFINE(struct FL_int, FL_int)

// packed vector

VECTOR_DEFINE(int, int)
PACKEDVECTOR_DEFINE(int, int)

VECTOR_DEFINE(int, Int)
COMPONENT_MANAGER_DEFINE(int, Int)
