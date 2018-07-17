#pragma once

#include "Lib/E_FreeList.h"

#include "Acceleration.h"
#include "Appearance.h"
#include "Entity.h"
#include "Position.h"
#include "Velocity.h"
// -----------------------------------------
//    Types
// -----------------------------------------

// god object of state
struct ECS_Components;
struct ECS_Components {
        struct E_FreeList
            free_elements;  // for keeping track of where to add and delete
                            // things in the sparse arrays

        // managers
        struct Entity_Manager entity_manager;
        struct Acceleration_Manager acceleration_manager;
        struct Velocity_Manager velocity_manager;
        struct Position_Manager position_manager;
        struct Appearance_Manager appearance_manager;
};

// -----------------------------------------
//    Procedures
// -----------------------------------------

// gets the next free index and marks that index as taken so that free index
// will no longer be a free idnex. Basically a wrapper for "freelist_add," and
// fills the added element with SIZE_MAX
size_t ECS_get_next_free_index(struct E_FreeList*);

// deletes an enttiy at a given point
void ECS_delete_entity_at(struct ECS_Components*, size_t);
