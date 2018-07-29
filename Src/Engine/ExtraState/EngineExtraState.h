#pragma once
#include "Lib/Time.h"
#include "Lib/V2.h"

struct EXS_GameCamera {
	struct V2 camera_velocity; // camera velocity
	struct V2 camera_position; // camera position
};


// The core type that contains "globally" required state
struct EXS_ExtraState;
struct EXS_ExtraState {
	struct EXS_GameCamera camera;
	Time dt; // time taken to render the frame
};

// initializes the extras with default values
void ECS_initExtraState(struct EXS_ExtraState *);

//
void EXS_applyCameraVelocity(struct EXS_ExtraState *);
