#pragma once

#include "../Components/Components.h"
#include "../Resources/ResourceRegistry.h"
#include "../ExtraState/EngineExtraState.h"
#include "../EventManager/EventManager.h"
/**
 * EventEffects.h --> functions that cast IO actions upon the world. should be
 * used as a result of parsing the events.
 */


void EVT_changeCameraXVelocity(
	struct EXS_ExtraState *extraState,
	const EVT_CameraXVelocitySignal cameraMovementSignal);

void EVT_changeCameraYVelocity(
	struct EXS_ExtraState *extraState,
	const EVT_CameraYVelocitySignal cameraMovementSignal);

void EVT_decelerateCameraX(
	struct EXS_ExtraState *extraState,
	const EVT_CameraXDecelerateSignal cameraDecelerateSignal);

void EVT_decelerateCameraY(
	struct EXS_ExtraState *extraState,
	const EVT_CameraYDecelerateSignal cameraDecelerateSignal);

// TODO more on building / spawining stuff as awell. Currently only supports
// building
void EVT_buildGameObject(struct CPT_Components *components,
			 struct RSC_ResourceRegistry *resources,
			 struct EXS_ExtraState *extraState,
			 EVT_BuildSignal buildStationSignal);

// TODO this is gonna be a god func
void EVT_leftMousePressHandler(const struct CPT_Components *components,
			       const struct EXS_ExtraState *);
