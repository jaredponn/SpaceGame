#include "InputHandler.h"

// static read only global variable of the mouse's position and scroll direction
static struct INP_MouseState globalMouseState;

// -----------------------------------------
//    Procedures
// -----------------------------------------

void INP_initMouseState() {
        globalMouseState =
            (struct INP_MouseState){.mouse_position = (struct V2){0, 0},
                                    .scroll_direction = (struct V2){0, 0}};
}

void INP_parseInputs(SDL_Event* sdlEvent, struct INP_InputMap* inputMap,
                     struct Event_Vector* eventManager) {
        size_t keyReleaseVecLength =
            KeyBind_vector_size(&inputMap->keyReleaseMappings);
        size_t keyPressVecLength =
            KeyBind_vector_size(&inputMap->keyPressMappings);

        size_t mouseKeyPressedVecLength =
            MouseKeyBind_vector_size(&inputMap->mouseButtonPressMappings);
        size_t mouseKeyReleaseVecLength =
            MouseKeyBind_vector_size(&inputMap->mouseButtonReleaseMappings);

        while (SDL_PollEvent(sdlEvent)) {
                // changes the button states (mouse and keyboard)
                switch (sdlEvent->type) {
                        case SDL_KEYUP:
                                for (size_t i = 0; i < keyReleaseVecLength;
                                     ++i) {
                                        if (sdlEvent->key.keysym.scancode ==
                                            KeyBind_vector_get(
                                                &inputMap->keyReleaseMappings,
                                                i)
                                                .sdlKey)
                                                Event_vector_push_back(
                                                    eventManager,
                                                    KeyBind_vector_get(
                                                        &inputMap
                                                             ->keyReleaseMappings,
                                                        i)
                                                        .gameEvent);
                                }
                                break;

                        case SDL_KEYDOWN:
                                for (size_t i = 0; i < keyPressVecLength; ++i) {
                                        if (sdlEvent->key.keysym.scancode ==
                                            KeyBind_vector_get(
                                                &inputMap->keyPressMappings, i)
                                                .sdlKey)
                                                Event_vector_push_back(
                                                    eventManager,
                                                    KeyBind_vector_get(
                                                        &inputMap
                                                             ->keyPressMappings,
                                                        i)
                                                        .gameEvent);
                                }
                                break;

                        case SDL_MOUSEBUTTONDOWN:
                                for (size_t i = 0; i < mouseKeyPressedVecLength;
                                     ++i) {
                                        if (sdlEvent->button.button ==
                                            MouseKeyBind_vector_get(
                                                &inputMap
                                                     ->mouseButtonPressMappings,
                                                i)
                                                .sdlButton)
                                                Event_vector_push_back(
                                                    eventManager,
                                                    MouseKeyBind_vector_get(
                                                        &inputMap
                                                             ->mouseButtonPressMappings,
                                                        i)
                                                        .gameEvent);
                                }
                                break;

                        case SDL_MOUSEBUTTONUP:
                                for (size_t i = 0; i < mouseKeyReleaseVecLength;
                                     ++i) {
                                        if (sdlEvent->button.button ==
                                            MouseKeyBind_vector_get(
                                                &inputMap
                                                     ->mouseButtonReleaseMappings,
                                                i)
                                                .sdlButton)
                                                Event_vector_push_back(
                                                    eventManager,
                                                    MouseKeyBind_vector_get(
                                                        &inputMap
                                                             ->mouseButtonReleaseMappings,
                                                        i)
                                                        .gameEvent);
                                }
                                break;

                        case SDL_MOUSEWHEEL:
                                globalMouseState.scroll_direction =
                                    (struct V2){.x = (float)sdlEvent->wheel.x,
                                                .y = (float)sdlEvent->wheel.y};

                                Event_vector_push_back(
                                    eventManager, inputMap->mouseScrollEvent);
                                break;

                        case SDL_MOUSEMOTION:
                                globalMouseState.mouse_position =
                                    (struct V2){.x = (float)sdlEvent->button.x,
                                                .y = (float)sdlEvent->button.y};

                                Event_vector_push_back(
                                    eventManager, inputMap->mouseMovementEvent);
                                break;
                        case SDL_QUIT: {
                                exit(1);
                        }

                        default:
                                break;
                }
        }
}

const struct V2* INP_getMousePosition() {
        return &globalMouseState.mouse_position;
}

const struct V2* INP_getScroll() { return &globalMouseState.scroll_direction; }
