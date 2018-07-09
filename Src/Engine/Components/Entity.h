#pragma once

#include "Lib/E_FreeList.h"
#include "Lib/GenericVector.h"

// -----------------------------------------
//    Entity
// -----------------------------------------

// bit shifted integer corrosponding to the enum Componenets that keeps track of
// which Components the entity contains
typedef unsigned int Entity;
VECTOR_DECLARE(Entity, Entity)

struct Entity_Manager;
struct Entity_Manager {
        struct Entity_Vector entities;
        struct E_FreeList free_elements;
};

// -----------------------------------------
//    Components
// -----------------------------------------
typedef enum CPT_Components {
        COMPONENT_NONE = 1 << 0,
        COMPONENT_POSITION = 1 << 1,
        COMPONENT_APPEARANCE = 1 << 2

} CPT_Components;

// -----------------------------------------
//    Procedures
// -----------------------------------------

// initializes the entity manager
void Entity_manager_init(struct Entity_Manager*, size_t);

// adds a new entity to the Entity Manager, and returns where it was added
size_t Entity_manager_add_new_entity(struct Entity_Manager* entityManager,
                                     const Entity newEntity);

// lazily delete an entity at a point, and returns the deleted Entity
Entity Entity_manager_remove(struct Entity_Manager* entityManager,
                             const size_t index);
