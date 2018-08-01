#pragma once

#include "Lib/GenericVector.h"
#include "Lib/V2.h"
/**
 * Event manager
 * The eventmanager is a vector of Events. The Event is a wrapper around a type
 * and the Signal (each input event can be thought of as a signal from a system)
 */

// -----------------------------------------
//    Primitive event types
// -----------------------------------------

// enum to keep track of the different types an event could be
typedef enum EVT_Type {
	EVT_Empty,  /**< no event*/
	EVT_SpawnA, /**< basic spawn signal */
	EVT_SpawnB, /**< basic spawn signal */

	EVT_Collision, /**< basic collision signal */

	EVT_CameraVelocity,   /**< changes camera velocity and sets acceleration
				 to 0 */
	EVT_CameraDecelerate, /**< decelerates the camera */
} EVT_Type;

// the global_index of the entities that have collided
typedef struct EVT_CollisionSignal {
	size_t a; /**< id of the first entity that collided */
	size_t b; /**< id of the second entity */
} EVT_CollisionSignal;

typedef struct V2 EVT_CameraVelocitySignal;
typedef struct V2 EVT_CameraDecelerateSignal;

// -----------------------------------------
//    Higher order event types
// -----------------------------------------
// Event type
typedef struct Event {
	EVT_Type type; /**< type that each event should have */

	/** signals of possible events */
	union {
		EVT_CollisionSignal collision;
		EVT_CameraVelocitySignal camera_velocity;
		EVT_CameraDecelerateSignal camera_decelerate;
	};

} Event;

// -----------------------------------------
//    Event manager
// -----------------------------------------
// the event manager is a wrapper around a vector object
VECTOR_TYPE_DECLARE(Event, EventManager)

// -----------------------------------------
//    Event effects -- effects to run given an event
// -----------------------------------------
