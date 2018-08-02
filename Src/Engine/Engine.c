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

#include "EventManager/EventEffects.h"

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
		   struct ECS_ResourceRegistry *resourceRegistry,
		   struct INP_InputMap *inputMap,
		   struct EventManager *engineEventManager,
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
		SYS_updatePositions(CPT_getPositionManager(engineComponents),
				    CPT_getAppearance0Manager(engineComponents),
				    CPT_getRectAabb0Manager(engineComponents),
				    CPT_getRectAabb1Manager(engineComponents),
				    CPT_getCircAabb0Manager(engineComponents),
				    CPT_getCircAabb1Manager(engineComponents));

		EXS_applyCameraMovement(engineExtraState);

		SYS_renderCopy(resourceRegistry->renderer,
			       CPT_getAppearance0Manager(engineComponents),
			       &engineExtraState->camera);

		// debug renderers
		SYS_renderDebugRectAabb(
			resourceRegistry->renderer,
			CPT_getRectAabb1Manager(engineComponents),
			&engineExtraState->camera, 255, 0, 0, 255);

		SYS_renderDebugCircAabb(
			resourceRegistry->renderer,
			CPT_getCircAabb0Manager(engineComponents),
			&engineExtraState->camera, 0, 255, 0, 255);


		SYS_circRectAabbHitTest(
			CPT_getCircAabb0Manager(engineComponents),
			CPT_getRectAabb1Manager(engineComponents),
			engineEventManager);

		// rendering
		SDL_RenderPresent(resourceRegistry->renderer);

		// input handling / sending events ot the event mangager
		INP_parseInputs(&sdlEvent, inputMap, engineEventManager);

		// parsing the events
		{
			size_t eventVectorLength =
				EventManager_size(engineEventManager);

			Event gameEvent;

			for (size_t i = 0; i < eventVectorLength; ++i) {
				gameEvent =
					EventManager_get(engineEventManager, i);
				switch (gameEvent.type) {

				case EVT_SpawnA:
					EVT_spawnTestARect(engineComponents,
							   resourceRegistry,
							   engineExtraState);
					break;

				case EVT_SpawnB:
					EVT_spawnTestBRect(engineComponents,
							   resourceRegistry,
							   engineExtraState);
					break;

				case EVT_LeftMousePress:
					EVT_leftMousePressHandler(
						engineComponents,
						engineExtraState);
					break;

				case EVT_Collision: {
					CPT_deleteEntityAt(
						engineComponents,
						gameEvent.collision.a);

					CPT_deleteEntityAt(
						engineComponents,
						gameEvent.collision.b);
				} break;

					/** camera movement events */
				case EVT_CameraXVelocity: {
					EVT_changeCameraXVelocity(
						engineExtraState,
						gameEvent.camera_x_velocity);
				} break;
				case EVT_CameraYVelocity: {
					EVT_changeCameraYVelocity(
						engineExtraState,
						gameEvent.camera_y_velocity);
				} break;
				case EVT_CameraXDecelerate: {
					EVT_decelerateCameraX(
						engineExtraState,
						gameEvent.camera_x_decelerate);
				} break;
				case EVT_CameraYDecelerate: {
					EVT_decelerateCameraY(
						engineExtraState,
						gameEvent.camera_y_decelerate);
				} break;

				default:
					break;
				}
			}

			EventManager_lazy_clear(engineEventManager);
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
