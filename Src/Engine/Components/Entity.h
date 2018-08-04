#pragma once

#include <stdint.h>
#include "Lib/GenericComponentManager.h"
#include "Lib/GenericVector.h"

// -----------------------------------------
//    Entity
// -----------------------------------------

// bit shifted integer corrosponding to the enum Componenets that keeps track of
// which Components the entity contains
typedef enum CPT_Entity Entity;

// how the different components are classified
enum CPT_Entity {
	CPT_NONE = 1 << 0,
	CPT_SOLARSTATION = 1 << 1,

};

VECTOR_DECLARE(Entity, Entity)
COMPONENT_MANAGER_DECLARE(Entity, Entity, Entity)
