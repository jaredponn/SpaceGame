#pragma once
#include "Lib/Time.h"
#include "Lib/V2.h"
#include "Lib/sizet_Vector.h"

struct EXS_GameCamera {
	struct V2 camera_acceleration; // camera acceleration
	struct V2 camera_velocity;     // camera velocity
	struct V2 camera_position;     // camera position

	struct V2 camera_zoom_acceleration;
	struct V2 camera_zoom_velocity;
	struct V2 camera_zoom_position;
};

enum EXS_PlayerActionState {
	EXS_Nothing,
	EXS_BuildSolarTower,
};

// The core type that contains "globally" required state
struct EXS_ExtraState;
struct EXS_ExtraState {
	Time dt; /**< time taken to render the frame */
	enum EXS_PlayerActionState player_action_state;
	struct SizetVector focused_entities; /**< global indicies of entities
						currently focused  */
	struct EXS_GameCamera camera; /**< things relating to the game camera */
};

// initializes the extras with default values
void ECS_initExtraState(struct EXS_ExtraState *);

//
void EXS_applyCameraMovement(struct EXS_ExtraState *);
