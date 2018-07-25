#include "Engine.h"
#include "Lib/Time.h"

#include "Systems/ApplyMovementTransforms.h"
#include "Systems/RenderCopy.h"
#include "Systems/UpdatePositions.h"

#include "Components/Components.h"
#include "Components/ComponentsGenerics.h"
#include "Components/MovementGenerics.h"

#include "Input/GameInputMaps.h"
#include "Input/InputHandler.h"

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

// -----------------------------------------
//    Constants
// -----------------------------------------
const float FPS = 1.f / 64;

// -----------------------------------------
//    Private declartaions
// -----------------------------------------

// sleeps the engine to not overuse cpu
static void ECS_sleep(float FPS, Time dt);

// -----------------------------------------
//    Procedures
// -----------------------------------------

void ECS_initLibraries() {
        RSC_initSDL(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
        RSC_initSDLImage(IMG_INIT_PNG);
}

void ECS_initInput(struct INP_InputMap *inputMap) {
        INP_initInputMap(inputMap);
        INP_initMouseState();
}

void ECS_runEngine(struct CPT_Set *engineCptSets,
                   struct ECS_ResourceRegistry *resourceRegistry,
                   struct INP_InputMap *inputMap,
                   struct EventManager *engineEventManager,
                   struct ECS_ExtraState *engineExtraState) {
        // declarations
        SDL_Event sdlEvent; /**< sdl event */
        Time t_i, t_f;      /**< time for calculating the time delta */

        INP_setDefaultMap(inputMap);

        while (1) {
                // timing the frame
                t_i = UTI_getCurTime();

                // clears the background to black
                SDL_SetRenderDrawColor(resourceRegistry->cRenderer, 0, 0, 0, 0);
                SDL_RenderClear(resourceRegistry->cRenderer);

                Appearance test = (Appearance){
                    .texture =
                        resourceRegistry->cResources.cTextures.testTexture,
                    .srcrect = (SDL_Rect){.x = 0, .y = 0, .w = 100, .h = 100},
                    .dstrect = (SDL_Rect){.x = 0, .y = 0, .w = 100, .h = 100},
                    .angle = 0};

                // running the systems / sending events to the event manager
                SYS_applyAcceleration(
                    CPT_managerGet(Acceleration)(engineCptSets),
                    CPT_managerGet(Velocity)(engineCptSets),
                    engineExtraState->dt);

                SYS_applyVelocity(CPT_managerGet(Velocity)(engineCptSets),
                                  CPT_managerGet(Position)(engineCptSets),
                                  engineExtraState->dt);
                SYS_updatePositions(CPT_managerGet(Position)(engineCptSets),
                                    CPT_managerGet(Appearance)(engineCptSets));

                SYS_renderCopy(resourceRegistry->cRenderer,

                               CPT_managerGet(Appearance)(engineCptSets));

                // rendering
                SDL_RenderPresent(resourceRegistry->cRenderer);

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
                                        case EVT_Spawn: {
                                                CPT_updateCurFreeIndex(
                                                    engineCptSets);

                                                // adding acceleration
                                                CPT_addComponent(
                                                    engineCptSets,
                                                    &(Acceleration){.x = 0,
                                                                    .y = -2});

                                                // adding velocity
                                                CPT_addComponent(
                                                    engineCptSets,
                                                    &(Velocity){.x = 0,
                                                                .y = -2});

                                                // adding position
                                                Position transform = (Position){
                                                    .x = 50, .y = 50};
                                                Position tmppos = MVT_sub(
                                                    (const Position *)
                                                        INP_getMousePosition(),
                                                    &transform);
                                                CPT_addComponent(engineCptSets,
                                                                 &tmppos);

                                                // adding appearance
                                                Appearance tmpapp = test;
                                                CPT_addComponent(engineCptSets,
                                                                 &tmpapp);
                                        } break;
                                        case EVT_Collision:
                                                break;
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

void ECS_quitLibraries() {
        SDL_Quit();
        IMG_Quit();
}
// -----------------------------------------
//    Private function implementations
// -----------------------------------------

static void ECS_sleep(float FPS, Time dt) {
        UTI_sleep(FPS > UTI_castTimeToSecs(dt)
                      ? UTI_timeDiff(UTI_castSecsToTime(FPS), dt)
                      : UTI_zeroTime());
}
