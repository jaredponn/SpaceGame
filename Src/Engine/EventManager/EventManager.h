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

} EVT_Event;

// Event type
typedef struct Event {
        unsigned int type;      /**< type that each event should have */
        union EVT_Signal event; /**< data for the event */
} Event;

VECTOR_DECLARE(Event, Event)

struct ECS_EventManager {
        struct Event_Vector events; /**< list of events */
};

// -----------------------------------------
//    Procedures
// -----------------------------------------

// pushes an event
void EVT_push_back(struct ECS_EventManager*, const Event*);

// gets a const pointer to vector
const struct Event_Vector* EVT_get_events(const struct ECS_EventManager*);

// lazily clears the events in the event manager
void EVT_clear(struct ECS_EventManager*);

// initlizes the event manager with a given size_t
void ECS_initEventManager(struct ECS_EventManager*, size_t);
