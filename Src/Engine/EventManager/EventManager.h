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
	EVT_SpawnA,    /**< basic spawn signal */
	EVT_SpawnB,    /**< basic spawn signal */
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

// Event type
typedef struct Event {
	EVT_Type type; /**< type that each event should have */

	/** signals of possible events */
	union {
		EVT_CollisionSignal collision;
	};

} Event;

// the event manager is a wrapper around a vector object
VECTOR_TYPE_DECLARE(Event, EventManager)
