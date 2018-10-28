#pragma once
#include "mmacros.h"

/** minternals.h -- macros for helping generate the data structures
 *
 */

#define MK_FUNC(NAME, FUNC_NAME) MCAT(NAME, _##FUNC_NAME)
