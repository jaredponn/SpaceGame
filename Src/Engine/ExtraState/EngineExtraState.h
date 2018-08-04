#pragma once
#include "Lib/Time.h"
#include "Lib/V2.h"
#include "Lib/sizet_Vector.h"
#include <stdbool.h>

// play resources
struct EXS_GameCamera {
	struct V2 camera_acceleration; // camera acceleration
	struct V2 camera_velocity;     // camera velocity
	struct V2 camera_position;     // camera position
	float camera_movement_velocity;
	float camera_movement_deceleration;

	struct V2 camera_zoom_acceleration;
	struct V2 camera_zoom_velocity;
	struct V2 camera_zoom_position;
};

// player resources
struct EXS_PlayerResources {
	unsigned int gold;
	unsigned int energy;
};

enum EXS_PlayerActionState {
	EXS_Idle,     /**< idle playerstate */
	EXS_TryBuild, /**< state where the player is trying to build something
			 and they have the cool semi transparent viser thing */
};

// The core type that contains "globally" required state
struct EXS_ExtraState;
struct EXS_ExtraState {
	Time dt; /**< time taken to render the frame */

	struct EXS_PlayerResources
		player_resources; /**< player resources (gold /energy) */


	enum EXS_PlayerActionState
		player_action_state; /**< TODO maybe use for a giant state
					machine later */

	struct EXS_GameCamera camera; /**< things relating to the game camera */
};

// initializes the extras with default values
void ECS_initExtraState(struct EXS_ExtraState *);

// applies the camera movement
void EXS_applyCameraMovement(struct EXS_ExtraState *);

// returns true if there are enough resources
bool EXS_hasEnoughResources(struct EXS_ExtraState *, unsigned int gold,
			    unsigned int energy);

// subtracts the amount from the resources
void EXS_subtractResources(struct EXS_ExtraState *, unsigned int gold,
			   unsigned int energy);

// sets the player action state to whatever
void EXS_setPlayerActionState(struct EXS_ExtraState *,
			      enum EXS_PlayerActionState);
