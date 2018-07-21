#include "Engine.h"
#include "Lib/Time.h"

#include "InputManager/Input.h"

#include "Systems/ApplyMovementTransforms.h"
#include "Systems/Render.h"
#include "Systems/UpdatePositions.h"

#include "Components/EngineComponentGenerics.h"
#include "Components/EngineComponents.h"
#include "Components/MovementGenerics.h"

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
        INP_init();
}

void ECS_runEngine(struct ECS_Components *engineComponents,
                   struct ECS_ResourceRegistry *resourceRegistry,
                   struct ECS_EventManager *engineEventManager,
                   struct ECS_ExtraState *engineExtraState) {
        // declarations
        SDL_Event e;
        Time t_i, t_f;
        size_t nextGlobalFreeIndex = 0;

        while (1) {
                // timing the frame
                t_i = UTI_getCurTime();

                // event handling
                INP_updateInputState(&e);

                // clears the background to black
                SDL_SetRenderDrawColor(resourceRegistry->cRenderer, 0, 0, 0, 0);
                SDL_RenderClear(resourceRegistry->cRenderer);

                // other shit
                Appearance test = (Appearance){
                    .texture =
                        resourceRegistry->cResources.cTextures.testTexture,
                    .srcrect = (SDL_Rect){.x = 0, .y = 0, .w = 100, .h = 100},
                    .dstrect = (SDL_Rect){.x = 0, .y = 0, .w = 100, .h = 100},
                    .angle = 0};

                // function
                if (INP_onKeyReleaseTap(SDL_SCANCODE_A)) {
                        nextGlobalFreeIndex = ECS_get_next_free_index(
                            &engineComponents->free_elements);

                        // adding acceleration
                        Acceleration tmpacc = (Acceleration){.x = 0, .y = -2};
                        ECS_add_elem_at(engineComponents, &tmpacc,
                                        nextGlobalFreeIndex);

                        // adding velocity
                        Velocity tmpvel = (Velocity){.x = 0, .y = -2};
                        ECS_add_elem_at(engineComponents, &tmpvel,
                                        nextGlobalFreeIndex);

                        // adding position
                        Position transform = (Position){.x = 50, .y = 50};
                        Position tmppos =
                            MVT_sub((const Position *)INP_getMousePosition(),
                                    &transform);
                        ECS_add_elem_at(engineComponents, &tmppos,
                                        nextGlobalFreeIndex);

                        // adding appearance
                        Appearance tmpapp = test;
                        ECS_add_elem_at(engineComponents, &tmpapp,
                                        nextGlobalFreeIndex);
                }

                // updated the old input state
                INP_updateOldState();

                // running the systems
                SYS_applyAcceleration(
                    ECS_manager_get(Acceleration)(engineComponents),
                    ECS_manager_get(Velocity)(engineComponents),
                    engineExtraState->dt);

                SYS_applyVelocity(ECS_manager_get(Velocity)(engineComponents),
                                  ECS_manager_get(Position)(engineComponents),
                                  engineExtraState->dt);
                SYS_updatePositions(
                    ECS_manager_get(Position)(engineComponents),
                    ECS_manager_get(Appearance)(engineComponents));

                SYS_renderCopy(resourceRegistry->cRenderer,

                               ECS_manager_get(Appearance)(engineComponents));

                // rendering
                SDL_RenderPresent(resourceRegistry->cRenderer);

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
