#pragma once

#include "../Components/Components.h"
#include "../Resources/ResourceRegistry.h"
#include "../ExtraState/EngineExtraState.h"
#include "../EventManager/EventManager.h"
/**
 * EventEffects.h --> functions that cast IO actions upon the world. should be
 * used as a result of parsing the events.
 */


void EVT_spawnTestARect(struct CPT_Components *components,
			const struct ECS_ResourceRegistry *resources,
			const struct EXS_ExtraState *);

void EVT_spawnTestBRect(struct CPT_Components *components,
			const struct ECS_ResourceRegistry *resources,
			const struct EXS_ExtraState *);

void EVT_updateCameraVelocity(struct EXS_ExtraState *,
			      const EVT_CameraMovementSignal *);
