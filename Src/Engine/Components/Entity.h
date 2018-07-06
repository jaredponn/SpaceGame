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

struct EntityManager;
struct EntityManager {
        struct Entity_Vector entities;
        struct E_FreeList free_elements;
};

// -----------------------------------------
//    Components
// -----------------------------------------
typedef enum Components {
        COMPONENT_NONE = 1 << 0,
        COMPONENT_POSITION = 1 << 1,
        COMPONENT_APPEARANCE = 1 << 2

} Components;

// -----------------------------------------
//    Utility types
// -----------------------------------------

typedef struct EntityIndex_Tuple {
        size_t index;   // index of the entity
        Entity entity;  // actual entity
} EntityPos_Tuple;

// -----------------------------------------
//    Procedures
// -----------------------------------------

// initializes the entity manager
void initEntityManager(struct EntityManager*, size_t);

// adds a new entity to the Entity Manager, and returns where it was added
size_t addNewEntity(struct EntityManager* entityManager,
                    const Entity newEntity);

// lazily delete an entity at a point, and returns the deleted Entity
Entity deleteEntity(struct EntityManager* entityManager, const size_t index);
