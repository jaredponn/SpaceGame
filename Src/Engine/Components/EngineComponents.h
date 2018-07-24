#pragma once

// lib includes
#include "Lib/E_FreeList.h"
#include "Lib/GenericComponentManager.h"
#include "Lib/GenericVector.h"

#include "Aabb.h"
#include "Appearance.h"
#include "Entity.h"
#include "Movement.h"

// -----------------------------------------
//    Macros
// -----------------------------------------

// listof components using X macros
#define LIST_OF_COMPONENTS  \
        X_CPT(Entity)       \
        X_CPT(Position)     \
        X_CPT(Velocity)     \
        X_CPT(Acceleration) \
        X_CPT(Appearance)   \
        X_CPT(Aabb)

// Defines how to name the managers in ECS_Components
#define MANAGER_NAME(name) m_##name

// defines how to name the manger getters from a ECS_Components
#define MANAGER_GETTER_NAME(name) ECS_get_##name##_manager

// -----------------------------------------
//    Declaring the component managers
// -----------------------------------------

// declares the component managers:
#define X_CPT(name)                \
        VECTOR_DECLARE(name, name) \
        COMPONENT_MANAGER_DECLARE(name, name)
LIST_OF_COMPONENTS
#undef X_CPT

// -----------------------------------------
//    Types
// -----------------------------------------

// god object of state
struct ECS_Components;
struct ECS_Components {
        struct E_FreeList
            free_elements;  // for keeping track of where to add and delete
                            // things in the sparse arrays

        // clang-format off
        // putting the managers inside of this struct
        #define X_CPT(name) struct name##_Manager MANAGER_NAME(name);
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

// getter for the managers from ECS_Components. returns a non const pointer so
// permits editing of the manager
/*Example usage: To get the Apearance component
 * ECS_manager_get(Appearance)(engineComponents_p);
 */
#define ECS_manager_get(type) MANAGER_GETTER_NAME(type)

// declaring getters for the managers
#define X_CPT(name)                                       \
        struct name##_Manager* MANAGER_GETTER_NAME(name)( \
            struct ECS_Components*);
LIST_OF_COMPONENTS
#undef X_CPT

// ECS_add_TYPE_at()
/* declares the generic ECS_add_elem_at(...) function
 * work
 */
#define X_CPT(type) \
        void ECS_add##type##At(struct ECS_Components*, type*, size_t);
LIST_OF_COMPONENTS
#undef X_CPT

// deletes an enttiy at a given point
void ECS_deleteEntityAt(struct ECS_Components*, size_t);

// frees the components
void ECS_freeComponents(struct ECS_Components*);
