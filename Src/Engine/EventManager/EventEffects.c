#include "EventEffects.h"
#include "../Input/InputHandler.h"
#include "../Input/Mouse.h"

// returns the sign of a value
#define SIGN(x) ((x > 0) - (x < 0))

// -----------------------------------------
//    building event handlers
// -----------------------------------------

static inline void EVT_buildSolarStation(struct CPT_Components *,
					 struct RSC_ResourceRegistry *);

void EVT_buildGameObject(struct CPT_Components *components,
			 struct RSC_ResourceRegistry *resources,
			 struct EXS_ExtraState *extraState,
			 EVT_BuildSignal buildSignal)
{
	if (EXS_hasEnoughResources(extraState, buildSignal.gold_price,
				   buildSignal.energy_price)) {
		switch (buildSignal.station_type) {
		case SOLAR_STATION:
			EVT_buildSolarStation(components, resources);
			break;

		case LASER_STATION:
			// TODO NO LASER STATION YET
			break;

		case MISSILE_STATION:
			// TODO No MISSILE STATION YET
			break;
		}
	}
}


static inline void EVT_buildSolarStation(struct CPT_Components *components,
					 struct RSC_ResourceRegistry *registry)
{
}

// -----------------------------------------
//    camera event handlers
// -----------------------------------------

void EVT_changeCameraXVelocity(
	struct EXS_ExtraState *extraState,
	const EVT_CameraXVelocitySignal cameraMovementSignal)
{
	extraState->camera.camera_velocity.x = cameraMovementSignal;
	extraState->camera.camera_acceleration.x = 0;
}

void EVT_changeCameraYVelocity(
	struct EXS_ExtraState *extraState,
	const EVT_CameraYVelocitySignal cameraMovementSignal)
{
	extraState->camera.camera_velocity.y = cameraMovementSignal;
	extraState->camera.camera_acceleration.y = 0;
}

void EVT_decelerateCameraX(
	struct EXS_ExtraState *extraState,
	const EVT_CameraXDecelerateSignal cameraDecelerateSignal)
{
	// predicate to ensuure that the player cant go hyper speeds
	if (SIGN(extraState->camera.camera_velocity.x)
		    + SIGN(cameraDecelerateSignal)
	    == 0) {
		extraState->camera.camera_acceleration.x =
			cameraDecelerateSignal;
	}
}

void EVT_decelerateCameraY(
	struct EXS_ExtraState *extraState,
	const EVT_CameraYDecelerateSignal cameraDecelerateSignal)
{
	if (SIGN(extraState->camera.camera_velocity.y)
		    + SIGN(cameraDecelerateSignal)
	    == 0) {

		extraState->camera.camera_acceleration.y =
			cameraDecelerateSignal;
	}
}

// -----------------------------------------
//    internals
// -----------------------------------------

void EVT_leftMousePressHandler(const struct CPT_Components *components,
			       const struct EXS_ExtraState *extraState)
{
	printf("this is gonna b efun");
}
