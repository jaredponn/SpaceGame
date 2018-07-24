#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "GenericPackedVector.h"
#include "sizet_Vector.h"

/**
 * Macros for a generic component manager with add, and remove fucntions. To use
 * this, ensure that you create a vector with the same TYPE and same PREFIX as
 * the component manager.
 */

// wrapper for a packed array
#define BASIC_COMPONENT_MANAGER_DECLARE(TYPE, PREFIX, VECPREFIX) \
        PACKEDVECTOR_TYPE_DECLARE(TYPE, PREFIX##Manager, VECPREFIX)

#define BASIC_COMPONENT_MANAGER_DEFINE(TYPE, PREFIX, VECPREFIX) \
        PACKEDVECTOR_TYPE_DEFINE(TYPE, PREFIX##Manager, VECPREFIX)
