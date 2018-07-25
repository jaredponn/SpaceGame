#pragma once

// lib includes
#include "Lib/E_FreeList.h"
#include "Lib/GenericComponentManager.h"
#include "Lib/GenericVector.h"
#include "Lib/Macros.h"

#include "Aabb.h"
#include "Appearance.h"
#include "Entity.h"
#include "Movement.h"

// -----------------------------------------
//    Macros
// -----------------------------------------

// listof components using X macros
#define LIST_OF_COMPONENTS                \
        /*X_CPT(TYPE, PREFIX)*/           \
        X_CPT(Entity, Entity)             \
        X_CPT(Position, Position)         \
        X_CPT(Velocity, Velocity)         \
        X_CPT(Acceleration, Acceleration) \
        X_CPT(Appearance, Appearance)     \
        X_CPT(Aabb, Aabb0)                \
        X_CPT(Aabb, Aabb1)

// Defines how to name the managers in ECS_Components
#define MANAGER_NAME(name) m_##name

// defines how to name the manger getters from a ECS_Components
#define MANAGER_GETTER_NAME(name) CPT_get##name##manager

// defines how to name the manger adders from a ECS_Components
#define MANAGER_ADD_AT_NAME(name) CPT_add##name##At

// defines how to name manager adders from a ECS_Components
#define MANAGER_ADD_NAME(name) CPT_add##name
// -----------------------------------------
//    Declaring the component managers
// -----------------------------------------

// declares the component managers:
#define X_CPT(type, name)          \
        VECTOR_DECLARE(type, name) \
        COMPONENT_MANAGER_DECLARE(type, name, name)
LIST_OF_COMPONENTS
#undef X_CPT

// -----------------------------------------
//    Types
// -----------------------------------------

// god object of state
struct ECS_Components;
struct ECS_Components {
        struct EFreeList
            free_elements;  // for keeping track of where to add and delete
                            // things in the sparse arrays

        // clang-format off
        // putting the managers inside of this struct
        #define X_CPT(type, name) struct name##Manager MANAGER_NAME(name);
        LIST_OF_COMPONENTS
        #undef X_CPT
        // clang-format on
};

// -----------------------------------------
//    Procedures
// -----------------------------------------

// initializes the compoenets engine. The size_t initialize size of the vectors
void ECS_initComponents(struct ECS_Components*, size_t);

// updates the next free index, so when calling ECS_getCurFreeIndex, it will
// give a free index. Basically a wrapper for
// "freelist_add," and fills the added element with SIZE_MAX
size_t ECS_updateCurFreeIndex(struct ECS_Components*);

// gets the current free index
size_t ECS_getCurFreeIndex(struct ECS_Components*);

// deletes an enttiy at a given point
void ECS_deleteEntityAt(struct ECS_Components*, size_t);

// frees the components
void ECS_freeComponents(struct ECS_Components*);

// -----------------------------------------
//    Getters
// -----------------------------------------
// getter for the managers from ECS_Components. returns a non const pointer so
// permits editing of the contents of the manager
/*Example usage: To get the Apearance component:
 * ECS_managerGet(Appearance)(engineComponents_p);
 */

#define ECS_managerGet(name) MANAGER_GETTER_NAME(name)

/// CPT_get<name>manager
#define X_CPT(type, name) \
        struct name##Manager* MANAGER_GETTER_NAME(name)(struct ECS_Components*);
LIST_OF_COMPONENTS
#undef X_CPT

// -----------------------------------------
//    Adders
// -----------------------------------------
// adds to the current index
#define ECS_addComponent(name) MANAGER_ADD_NAME(name)

// adds a component to a given index
#define ECS_addComponentAt(name) MANAGER_ADD_AT_NAME(name)

// ECS_add<name>At(components, index, val )
#define X_CPT(type, name) \
        void MANAGER_ADD_AT_NAME(name)(struct ECS_Components*, size_t, type*);
LIST_OF_COMPONENTS
#undef X_CPT

// ECS_add<name>(components, index, val )
#define X_CPT(type, name) \
        void MANAGER_ADD_NAME(name)(struct ECS_Components*, type*);
LIST_OF_COMPONENTS
#undef X_CPT
