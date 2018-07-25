#pragma once
#include "Components.h"
#include "Lib/Macros.h"

// -----------------------------------------
//    Generic functions for getting and adding to the component managers
// -----------------------------------------

// clang-format off
// generic add to function that automatically deduces the type of what is being
// added, and sends it to the appropriate manager
/* Example usage: to add something with an Position type
 * Position TEST = (Position) {3, 3};
 * CPT_addComponentAt(&TEST, 3);
 * // this will automatically deduce that TEST is of type Position and add it to index 3 of the Position manager
   */
#define X_CPT(type, name) type, name,

#define F_CPT_ADD(type, name) type*:MANAGER_ADD_AT_NAME(name),
#define CPT_addComponentAt(components, index, ...) _Generic((ID_VA_ARGS(__VA_ARGS__)), REMOVE_EXTRA_COMMA(DEFER1(MAP2)(F_CPT_ADD, LIST_OF_COMPONENTS))) (components, index, ID_VA_ARGS(__VA_ARGS__))

// adds component to the current free index
#define CPT_addComponent(components, ...) CPT_addComponentAt(components, CPT_getCurFreeIndex(components), ID_VA_ARGS(__VA_ARGS__))
