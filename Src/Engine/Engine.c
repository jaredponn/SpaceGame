#include "Engine.h"
#include "GameConfig.h"
#include "Lib/Time.h"

#include "Systems/ApplyMovementTransforms.h"
#include "Systems/Render.h"
#include "Systems/UpdatePositions.h"
#include "Systems/AabbHitTest.h"

#include "Components/Components.h"

#include "Input/GameInputMaps.h"
#include "Input/InputHandler.h"
#include "Input/Mouse.h"


#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

// -----------------------------------------
//    Private declartaions
// -----------------------------------------

// sleeps the engine to not overuse cpu
static void ECS_sleep(float fps, Time dt);

// -----------------------------------------
//    Procedures
// -----------------------------------------

void ECS_initLibraries()
{
	RSC_initSDL(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,
		    "2"); // mainly useless TODO remove
	RSC_initSDLImage(IMG_INIT_PNG);
}

void ECS_initInput(struct INP_InputMap *inputMap)
{
	INP_initInputMap(inputMap);
	INP_initMouseState();
}

void ECS_runEngine(struct CPT_Components *engineComponents,
		   struct RSC_ResourceRegistry *resourceRegistry,
		   struct INP_InputMap *inputMap,
		   struct EXS_ExtraState *engineExtraState)
{
	// declarations
	SDL_Event sdlEvent; /**< sdl event */
	Time t_i, t_f;      /**< times for calculating the time delta */

	INP_setDefaultMap(inputMap);

	while (1) {
		// timing the frame
		t_i = UTI_getCurTime();

		// clears the background to black
		SDL_SetRenderDrawColor(resourceRegistry->renderer, 31, 47, 50,
				       0);
		SDL_RenderClear(resourceRegistry->renderer);


		// running the systems / sending events to the event manager
		SYS_applyAcceleration(
			CPT_getAccelerationManager(engineComponents),
			CPT_getVelocityManager(engineComponents),
			engineExtraState->dt);

		SYS_applyVelocity(CPT_getVelocityManager(engineComponents),
				  CPT_getPositionManager(engineComponents),
				  engineExtraState->dt);

		SYS_updatePositions(
			CPT_getPositionManager(engineComponents),
			CPT_getStationAppearancesManager(engineComponents),
			CPT_getStationCircAabbsManager(engineComponents));

		EXS_applyCameraMovement(engineExtraState);

		SYS_renderCopy(
			resourceRegistry->renderer,
			CPT_getStationAppearancesManager(engineComponents),
			&engineExtraState->camera);

		SYS_renderDebugCircAabb(
			resourceRegistry->renderer,
			CPT_getStationCircAabbsManager(engineComponents),
			&engineExtraState->camera, 255, 0, 0, 100);


		// rendering
		SDL_RenderPresent(resourceRegistry->renderer);

		// input handling / executing game effects
		INP_parseInputs(&sdlEvent, inputMap, engineComponents,
				resourceRegistry, engineExtraState);

		// extra updates from the player action state TODO: update this
		// garbage design later
		if (engineExtraState->player_action_state == EXS_TryBuild) {
			struct BoolManager *focusManager =
				CPT_getFocusedManager(engineComponents);
			size_t tmpindex =
				BoolManager_get_index_from(focusManager, 0);

			struct V2 tmpv2 = INP_getWorldMousePosition(
				&engineExtraState->camera.camera_position);

			SYS_setElementPosition(
				CPT_getPositionManager(engineComponents),
				tmpindex, &tmpv2, &(struct V2){50, 50});
		}

		// sleeping to limit CPU usage
		ECS_sleep(FPS, engineExtraState->dt);

		// setting the time
		t_f = UTI_getCurTime();

		engineExtraState->dt = UTI_timeDiff(t_f, t_i);
	}
}

void ECS_quitLibraries()
{
	SDL_Quit();
	IMG_Quit();
}
// -----------------------------------------
//    Private function implementations
// -----------------------------------------

static void ECS_sleep(float fps, Time dt)
{
	UTI_sleep(FPS > UTI_castTimeToSecs(dt)
			  ? UTI_timeDiff(UTI_castSecsToTime(fps), dt)
			  : UTI_zeroTime());
}
