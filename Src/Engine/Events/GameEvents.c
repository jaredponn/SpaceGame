#include "GameEvents.h"
#include "../Input/Mouse.h"


// -----------------------------------------
//    private funcs
// -----------------------------------------

static inline void setCameraXVelocity(struct EXS_ExtraState *extraState,
				      float newVelocity);
static inline void setCameraYVelocity(struct EXS_ExtraState *extraState,
				      float newVelocity);
static inline void setCameraXAcceleration(struct EXS_ExtraState *extraState,
					  float newAccleration);
static inline void setCameraYAcceleration(struct EXS_ExtraState *extraState,
					  float newAccleration);
// returns the sign of a value
#define SIGN(x) ((x > 0) - (x < 0))
#define UNUSED(x) (void)(x)


// -----------------------------------------
//    spawning stations
// -----------------------------------------
void EVT_spawnNewSolarStation(struct CPT_Components *components,
			      struct RSC_ResourceRegistry *resources,
			      struct EXS_ExtraState *extraState)
{
	CPT_updateCurFreeIndex(components);

	// CPT_addAcceleration(components, &(Acceleration){.x = 0, .y = -2});
	CPT_addVelocity(components, &(Velocity){.x = 0, .y = -2});


	struct V2 mousePosition =
		INP_getWorldMousePosition(&extraState->camera.camera_position);
	struct V2 adjustedMousePosition =
		V2_sub(&mousePosition, &(struct V2){50, 50});

	CPT_addPosition(components, &adjustedMousePosition);

	CPT_addStationAppearances(
		components,
		&(struct Appearance){
			.texture = resources->resources.textures.testTexture,
			.srcrect =
				(SDL_Rect){
					.x = 0, .y = 0, .w = 1042, .h = 1042},
			.dstrect = (SDL_Rect){.x = adjustedMousePosition.x,
					      .y = adjustedMousePosition.y,
					      .w = 100,
					      .h = 100}});
}

// -----------------------------------------
//    camera event handlers
// -----------------------------------------


/**velocities ... */
void EVT_changeCameraVelocityRight(struct CPT_Components *components,
				   struct RSC_ResourceRegistry *resources,
				   struct EXS_ExtraState *extraState)
{
	UNUSED(components);
	UNUSED(resources);

	setCameraXVelocity(extraState,
			   extraState->camera.camera_movement_velocity);
}

void EVT_changeCameraVelocityLeft(struct CPT_Components *components,
				  struct RSC_ResourceRegistry *resources,
				  struct EXS_ExtraState *extraState)
{
	UNUSED(components);
	UNUSED(resources);

	setCameraXVelocity(extraState,
			   -extraState->camera.camera_movement_velocity);
}

void EVT_changeCameraVelocityUp(struct CPT_Components *components,
				struct RSC_ResourceRegistry *resources,
				struct EXS_ExtraState *extraState)
{
	UNUSED(components);
	UNUSED(resources);

	setCameraYVelocity(extraState,
			   -extraState->camera.camera_movement_velocity);
}
void EVT_changeCameraVelocityDown(struct CPT_Components *components,
				  struct RSC_ResourceRegistry *resources,
				  struct EXS_ExtraState *extraState)
{
	UNUSED(components);
	UNUSED(resources);
	setCameraYVelocity(extraState,
			   extraState->camera.camera_movement_velocity);
}

/**accelerations ... */
void EVT_decelerateCameraLeft(struct CPT_Components *components,
			      struct RSC_ResourceRegistry *resources,
			      struct EXS_ExtraState *extraState)
{
	UNUSED(components);
	UNUSED(resources);
	setCameraXAcceleration(extraState,
			       extraState->camera.camera_movement_deceleration);
}
void EVT_decelerateCameraRight(struct CPT_Components *components,
			       struct RSC_ResourceRegistry *resources,
			       struct EXS_ExtraState *extraState)
{
	UNUSED(components);
	UNUSED(resources);

	setCameraXAcceleration(
		extraState, -extraState->camera.camera_movement_deceleration);
}

void EVT_decelerateCameraUp(struct CPT_Components *components,
			    struct RSC_ResourceRegistry *resources,
			    struct EXS_ExtraState *extraState)
{
	UNUSED(components);
	UNUSED(resources);
	setCameraYAcceleration(extraState,
			       extraState->camera.camera_movement_deceleration);
}
void EVT_decelerateCameraDown(struct CPT_Components *components,
			      struct RSC_ResourceRegistry *resources,
			      struct EXS_ExtraState *extraState)
{
	UNUSED(components);
	UNUSED(resources);
	setCameraYAcceleration(
		extraState, -extraState->camera.camera_movement_deceleration);
}
// -----------------------------------------
//    other
// -----------------------------------------

void EVT_VOIDFUNC(struct CPT_Components *components,
		  struct RSC_ResourceRegistry *resources,
		  struct EXS_ExtraState *extraState)
{
	UNUSED(components);
	UNUSED(resources);
	UNUSED(extraState);
}

// -----------------------------------------
//    internals
// -----------------------------------------

static inline void setCameraXVelocity(struct EXS_ExtraState *extraState,
				      float newVelocity)
{
	extraState->camera.camera_velocity.x = newVelocity;
	extraState->camera.camera_acceleration.x = 0;
}

static inline void setCameraYVelocity(struct EXS_ExtraState *extraState,
				      float newVelocity)
{
	extraState->camera.camera_velocity.y = newVelocity;
	extraState->camera.camera_acceleration.y = 0;
}

static inline void setCameraXAcceleration(struct EXS_ExtraState *extraState,
					  float newAccleration)
{
	// predicate to ensuure that the player cant go hyper speeds
	if (SIGN(extraState->camera.camera_velocity.x) + SIGN(newAccleration)
	    == 0) {
		extraState->camera.camera_acceleration.x = newAccleration;
	}
}

static inline void setCameraYAcceleration(struct EXS_ExtraState *extraState,
					  float newAccleration)
{
	if (SIGN(extraState->camera.camera_velocity.y) + SIGN(newAccleration)
	    == 0) {
		extraState->camera.camera_acceleration.y = newAccleration;
	}
}
