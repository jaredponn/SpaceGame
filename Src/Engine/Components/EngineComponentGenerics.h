#pragma once
#include "EngineComponents.h"
#include "Lib/Macros.h"

// -----------------------------------------
//    Generic functions for getting and adding to the component managers
// -----------------------------------------

// clang-format off
// generic add to function that automatically deduces the type of what is being
// added, and sends it to the appropriate manager
/* Example usage: to add something with an Position type
 * Position TEST = (Position) {3, 3};
 * ECS_add_elem_at(&TEST, 3);
 * // this will automatically deduce that TEST is of type Position and add it to index 3 of the Position manager
   */
#define X_CPT(val) val,

#define F_CPT_ADD(type) type*:ECS_add_##type##_at,
#define ECS_add_elem_at(components, val, index) _Generic((val), REMOVE_EXTRA_COMMA(DEFER1(MAP)(F_CPT_ADD, LIST_OF_COMPONENTS))) (components, val, index)
