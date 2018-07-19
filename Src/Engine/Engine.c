#include "Engine.h"

#include "InputManager/Input.h"

#include "Systems/ApplyAcceleration.h"
#include "Systems/ApplyVelocity.h"
#include "Systems/Render.h"
#include "Systems/UpdatePositions.h"

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

// -----------------------------------------
//    Procedures
// -----------------------------------------

void ECS_initLibraries() {
        RSC_initSDL(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
        RSC_initSDLImage(IMG_INIT_PNG);
        INP_init();
}

void ECS_initComponents(struct ECS_Components *engineComponents,
                        size_t capacity) {
        E_freelist_init(&engineComponents->free_elements);
        E_freelist_reserve(&engineComponents->free_elements, capacity);

        Entity_manager_init(&engineComponents->entity_manager, capacity);
        Acceleration_manager_init(&engineComponents->acceleration_manager,
                                  capacity);
        Velocity_manager_init(&engineComponents->velocity_manager, capacity);
        Position_manager_init(&engineComponents->position_manager, capacity);
        Appearance_manager_init(&engineComponents->appearance_manager,
                                capacity);
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

void ECS_initExtras(struct ECS_Extras *engineCore) {
        engineCore->camera_position = (struct V2){.x = 0, .y = 0};
        engineCore->dt = 0;
}

// TODO TRY TO MAKE A RECTANGLE FALL DOwn THE SCREEN
void ECS_runEngine(struct ECS_Components *engineComponents,
                   struct ECS_ResourceRegistry *resourceRegistry,
                   struct ECS_Extras *engineExtras) {
        size_t tmp = 0;

        /** SDL_RenderClear(resourceRegistry->cRenderer); */

        while (1) {
                // event handling

                SDL_Event e;
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

                engineExtras->dt = 1;

                // fun
                if (INP_onKeyReleaseTap(SDL_SCANCODE_A)) {
                        tmp = ECS_get_next_free_index(
                            &engineComponents->free_elements);

                        Acceleration_manager_add_at(
                            &engineComponents->acceleration_manager, tmp,
                            (Acceleration){.x = 0, .y = -0.1});

                        Velocity_manager_add_at(
                            &engineComponents->velocity_manager, tmp,
                            (Velocity){.x = 0, .y = 10});

                        // testing
                        struct V2 transform = (struct V2){.x = 50, .y = 50};

                        Position_manager_add_at(
                            &engineComponents->position_manager, tmp,
                            V2_sub(INP_getMousePosition(), &transform));

                        Appearance_manager_add_at(
                            &engineComponents->appearance_manager, tmp, test);
                }

                V2_print(INP_getMousePosition());

                // dont forget to copy the keys
                INP_updateOldState();

                // running the systems
                SYS_applyAcceleration(&engineComponents->acceleration_manager,
                                      &engineComponents->velocity_manager,
                                      engineExtras->dt);
                SYS_applyVelocity(&engineComponents->velocity_manager,
                                  &engineComponents->position_manager,
                                  engineExtras->dt);
                SYS_updatePositions(&engineComponents->position_manager,
                                    &engineComponents->appearance_manager);
                SYS_renderCopy(resourceRegistry->cRenderer,
                               &engineComponents->appearance_manager);

                SDL_RenderPresent(resourceRegistry->cRenderer);
        }
}

void ECS_quitLibraries() {
        SDL_Quit();
        IMG_Quit();
}
