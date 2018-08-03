#pragma once

#include "../Components/Components.h"
#include "../ExtraState/EngineExtraState.h"
#include "../Resources/ResourceRegistry.h"
/**
 * Includes functions for the game events (events to be executed on a button
 * press for example).
 */

// typedef for the function pointers that modify game state
typedef void (*EVT_GameEventEffect)(struct CPT_Components *,
				    struct RSC_ResourceRegistry *,
				    struct EXS_ExtraState *);

// -----------------------------------------
//    building functions
// -----------------------------------------
void EVT_spawnNewSolarStation(struct CPT_Components *,
			      struct RSC_ResourceRegistry *,
			      struct EXS_ExtraState *);

// -----------------------------------------
//    Camera movement functions
// -----------------------------------------
// sets the velocity so the camera moves right with the camera_movement_velocity
// value
void EVT_changeCameraVelocityRight(struct CPT_Components *,
				   struct RSC_ResourceRegistry *,
				   struct EXS_ExtraState *);

// same as above but left
void EVT_changeCameraVelocityLeft(struct CPT_Components *,
				  struct RSC_ResourceRegistry *,
				  struct EXS_ExtraState *);


// sets the velocity so the camera moves up with the camera_movement_velocity
// value
void EVT_changeCameraVelocityUp(struct CPT_Components *,
				struct RSC_ResourceRegistry *,
				struct EXS_ExtraState *);

// same as above but down
void EVT_changeCameraVelocityDown(struct CPT_Components *,
				  struct RSC_ResourceRegistry *,
				  struct EXS_ExtraState *);

// setse the camera decleration so a camera moveing left will come to a stop
void EVT_decelerateCameraLeft(struct CPT_Components *,
			      struct RSC_ResourceRegistry *,
			      struct EXS_ExtraState *);
// setse the camera decleration so a camera moveing right will come to a stop
void EVT_decelerateCameraRight(struct CPT_Components *,
			       struct RSC_ResourceRegistry *,
			       struct EXS_ExtraState *);

void EVT_decelerateCameraUp(struct CPT_Components *,
			    struct RSC_ResourceRegistry *,
			    struct EXS_ExtraState *);

void EVT_decelerateCameraDown(struct CPT_Components *,
			      struct RSC_ResourceRegistry *,
			      struct EXS_ExtraState *);
// -----------------------------------------
//    extras
// -----------------------------------------
void EVT_VOIDFUNC(struct CPT_Components *, struct RSC_ResourceRegistry *,
		  struct EXS_ExtraState *);
