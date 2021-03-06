#pragma once

#include "Lib/MarkedFreeList.h"
#include "Lib/GenericComponentManager.h"
#include "Lib/GenericVector.h"
#include "Lib/Macros.h"

#include "Aabb.h"
#include "Appearance.h"
#include "Attribute.h"
#include "Entity.h"
#include "Movement.h"

/**
 * Components.h -> an aggregration of all the components in a single file.
 * Declares the CPT_Components struct -> a super struct (god object) that
 * contains all the compoents in it and associated getters, setters, and adders
 */
// -----------------------------------------
//    Macros
// -----------------------------------------

// listof components using X macros. Used to generate vectors, and packed
// vectors of the given type, prefixed by the type.
#define LIST_OF_COMPONENTS                                                     \
	/** X macros take arguments as follows:                                \
	 * X_CPT(type, manager's prefix, desired name)*/                       \
                                                                               \
	/** physics*/                                                          \
	X_CPT(Entity, Entity, Entity)                                          \
	X_CPT(struct V2, V2, Position)                                         \
	X_CPT(struct V2, V2, Velocity)                                         \
	X_CPT(struct V2, V2, Acceleration)                                     \
                                                                               \
	/** attributes*/                                                       \
	X_CPT(bool, Bool, Selectable)                                          \
	X_CPT(bool, Bool, Focused)                                             \
                                                                               \
	/** appearance layers*/                                                \
	X_CPT(struct Appearance, Appearance, StationAppearances)               \
                                                                               \
	/** collision layers*/                                                 \
	X_CPT(struct CircAabb, CircAabb, StationCircAabbs)


// Defines how to name the managers in CPT_Components
#define MANAGER_NAME(name) m_##name

// defines how to name the manger getters from a CPT_Components
#define MANAGER_GETTER_NAME(name) CPT_get##name##Manager

// defines how to name the manger adders from a CPT_Components
#define MANAGER_ADD_AT_NAME(name) CPT_add##name##At

// defines how to name manager adders from a CPT_Components
#define MANAGER_ADD_NAME(name) CPT_add##name
// -----------------------------------------
//    Declaring the component managers
// -----------------------------------------

// declares the component managers:
#define X_CPT(type, name)                                                      \
	VECTOR_DECLARE(type, name)                                             \
	COMPONENT_MANAGER_DECLARE(type, name, name)
#undef X_CPT

// -----------------------------------------
//    Types
// -----------------------------------------

// god object of state
struct CPT_Components;
struct CPT_Components {
	struct MarkedFreeList free_elements; /**< keepstrack of where to add and
					   delete things in the sparse arrays */

// clang-format off
        // putting the managers inside of this struct
        #define X_CPT(type,prefix, name) struct prefix##Manager MANAGER_NAME(name);
        LIST_OF_COMPONENTS
        #undef X_CPT
	// clang-format on
};

// -----------------------------------------
//    Procedures
// -----------------------------------------

// initializes the compoenets engine. The size_t initialize size of the vectors
void CPT_initComponents(struct CPT_Components *, size_t);

// updates the next free index, so when calling CPT_getCurFreeIndex, it will
// give a free index. Basically a wrapper for
// "freelist_add," and fills the added element with SIZE_MAX
void CPT_updateCurFreeIndex(struct CPT_Components *);

// gets the current free index
size_t CPT_getCurFreeIndex(struct CPT_Components *);

// deletes an enttiy at a given point
void CPT_deleteEntityAt(struct CPT_Components *, size_t);

// frees the components
void CPT_freeComponents(struct CPT_Components *);

// -----------------------------------------
//    Getters
// -----------------------------------------
// getter for the managers from CPT_Components. returns a non const pointer so
// permits editing of the contents of the manager
/*Example usage: To get the Apearance component:
 * CPT_managerGet(Appearance)(engineComponents_p);
 */

#define CPT_managerGet(name) MANAGER_GETTER_NAME(name)

/// CPT_get<name>manager
#define X_CPT(type, prefix, name)                                              \
	struct prefix##Manager *MANAGER_GETTER_NAME(name)(                     \
		struct CPT_Components *);
LIST_OF_COMPONENTS
#undef X_CPT

// -----------------------------------------
//    Adders
// -----------------------------------------
// strictly internals are here for the EngineComponentGenerics.h file

// CPT_add<name>At(components, index, val )
#define X_CPT(type, prefix, name)                                              \
	void MANAGER_ADD_AT_NAME(name)(struct CPT_Components *, size_t, type *);
LIST_OF_COMPONENTS
#undef X_CPT

// CPT_add<name>(components, index, val )
#define X_CPT(type, prefix, name)                                              \
	void MANAGER_ADD_NAME(name)(struct CPT_Components *, type *);
LIST_OF_COMPONENTS
#undef X_CPT
