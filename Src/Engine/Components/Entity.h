#pragma once

#include <stdint.h>
#include "Lib/GenericComponentManager.h"
#include "Lib/GenericVector.h"

// -----------------------------------------
//    Entity
// -----------------------------------------

// bit shifted integer corrosponding to the enum Componenets that keeps track of
// which Components the entity contains
typedef uint64_t Entity;

// how the different components are classified
typedef enum CPT_Components {
        CPT_NONE = 1 << 0,
        CPT_POSITION = 1 << 1,
        CPT_VELOCITY = 1 << 2,
        CPT_ACCELERATION = 1 << 3,
        CPT_APPEARANCE = 1 << 4

} CPT_Components;
