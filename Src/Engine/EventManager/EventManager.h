#pragma once

#include "Lib/GenericVector.h"
#include "Src/Engine/Components/Entity.h"
/**
 * Event manager ----
 * The eventmanager is a vector of Events. The Event is a wrapper around a type
 * and the Signal (each input event can be thought of as a signal from a system)
 */

// -----------------------------------------
//    Primitive event types
// -----------------------------------------

// enum to keep track of the different types an event could be
typedef enum EVT_Type {
        EVT_Empty,     /**< no event*/
        EVT_Spawn,     /**< basic spawn signal */
        EVT_Collision, /**< basic collision signal */
} EVT_Type;

// the global_index of the entities that have collided
typedef struct EVT_CollisionSignal {
        size_t a; /**< id of the first entity that collided */
        size_t b; /**< id of the second entity */
} EVT_CollisionSignal;

// -----------------------------------------
//    Higher order event types
// -----------------------------------------

// union that contains the data
typedef union EVT_Signal {
        EVT_CollisionSignal collision;
} EVT_Signal;

// Event type
typedef struct Event {
        EVT_Type type;           /**< type that each event should have */
        union EVT_Signal signal; /**< data for the event */
} Event;

VECTOR_DECLARE(Event, Event)
