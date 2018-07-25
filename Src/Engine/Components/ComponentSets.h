#pragma once

/** EngineComponentSets.h
 * Fuctions, and types for the component sets. A Component set is the type
 * CPT_Component, and this contains a vector that permits having different sets
 * (orlayers) of the CPT_Component type bundled in a vector.
 */

#include "Components.h"
#include "Lib/GenericVector.h"

// -----------------------------------------
//    macros
// -----------------------------------------

#define NUM_OF_COMPONENT_SETS 2

// -----------------------------------------
//    types
// -----------------------------------------

enum ECS_ComponentSets {
        SET0 = 0,
        SET1 = 1,
};
