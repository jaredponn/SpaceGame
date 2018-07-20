#pragma once
#include "Lib/Macros.h"
#include "Lib/V2Macros.h"
// -----------------------------------------
//    Macros
// -----------------------------------------

// X macro of the types of V2s we will have
#define LIST_OF_MOVEMENTS   \
        X_MVT(Acceleration) \
        X_MVT(Velocity)     \
        X_MVT(Position)

// Declaring the V2 functions
#define X_MVT(name) V2_DECLARE(name)
LIST_OF_MOVEMENTS
#undef X_MVT

// typedefing
#define X_MVT(name) typedef struct name name;
LIST_OF_MOVEMENTS
#undef X_MVT
