#include "Engine.h"
#include "Lib/Time.h"

#include "InputManager/Input.h"

#include "Systems/ApplyMovementTransforms.h"
#include "Systems/Render.h"
#include "Systems/UpdatePositions.h"

#include "Components/MovementGenerics.h"

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

// clang-format off
#define EXTRAS_PATH "/home/jared/Programs/SpaceGame/Extras"
// clang-format on

// -----------------------------------------
//    Constants
// -----------------------------------------
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const float FPS = 1.f / 64;

// -----------------------------------------
//    Procedures
// -----------------------------------------

void ECS_initLibraries() {
        RSC_initSDL(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
        RSC_initSDLImage(IMG_INIT_PNG);
        INP_init();
}

void ECS_loadInitResources(struct ECS_ResourceRegistry *resourceRegistry) {
        SDL_Window *window = RSC_createInitWindow(
            "Space Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

        SDL_Renderer *renderer =
            RSC_createInitRenderer(window, SDL_RENDERER_ACCELERATED);

        // TODO add proper error handling
        SDL_Texture *testTexture =
            RSC_loadImage(renderer, EXTRAS_PATH "/Images/bg.png");

        resourceRegistry->cWindow = window;
        resourceRegistry->cRenderer = renderer;
        resourceRegistry->cResources.cTextures.testTexture = testTexture;
}

void ECS_initExtraState(struct ECS_ExtraState *engineExtraState) {
        engineExtraState->camera_position = (struct V2){.x = 0, .y = 0};
        engineExtraState->dt = UTI_zeroTime();
}
void ECS_runEngine(struct ECS_Components *engineComponents,
                   struct ECS_ResourceRegistry *resourceRegistry,
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

                        Acceleration_manager_add_at(
                            ECS_manager_get(Acceleration)(engineComponents),
                            nextGlobalFreeIndex,
                            (Acceleration){.x = 0, .y = -2});

                        Velocity_manager_add_at(
                            ECS_manager_get(Velocity)(engineComponents),
                            nextGlobalFreeIndex, (Velocity){.x = 0, .y = 2});

                        // testing
                        Position transform = (Position){.x = 50, .y = 50};

                        Position_manager_add_at(
                            ECS_manager_get(Position)(engineComponents),
                            nextGlobalFreeIndex,
                            MVT_sub((const Position *)INP_getMousePosition(),
                                    &transform));

                        Appearance_manager_add_at(
                            ECS_manager_get(Appearance)(engineComponents),
                            nextGlobalFreeIndex, test);
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
                UTI_sleep(FPS > UTI_castTimeToSecs(engineExtraState->dt)
                              ? UTI_timeDiff(UTI_castSecsToTime(FPS),
                                             engineExtraState->dt)
                              : UTI_zeroTime());

                // setting the time
                t_f = UTI_getCurTime();

                engineExtraState->dt = UTI_timeDiff(t_f, t_i);
        }
}

void ECS_quitLibraries() {
        SDL_Quit();
        IMG_Quit();
}
