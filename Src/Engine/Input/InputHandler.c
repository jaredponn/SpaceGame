#include "InputHandler.h"

// static read only global variable of the mouse's position and scroll direction
static struct INP_MouseState globalMouseState;

// -----------------------------------------
//    Procedures
// -----------------------------------------

void ECS_InputMap_init(struct INP_InputMap* inputMap) {
        globalMouseState =
            (struct INP_MouseState){.mouse_position = (struct V2){0, 0},
                                    .scroll_direction = (struct V2){0, 0}};

        // initlizing the vectors
        KeyBind_vector_init(&inputMap->keyUpMappings);
        KeyBind_vector_init(&inputMap->keyDownMappings);

        MouseKeyBind_vector_init(&inputMap->mouseButtonUpMappings);
        MouseKeyBind_vector_init(&inputMap->mouseButtonDownMappings);

        inputMap->mouseMovementEvent = (Event){.type = EVT_Empty};
        inputMap->mouseScrollEvent = (Event){.type = EVT_Empty};
}

void INP_clearInputMap(struct INP_InputMap* inputMap) {
        // initlizing the vectors
        KeyBind_vector_lazy_clear(&inputMap->keyUpMappings);
        KeyBind_vector_lazy_clear(&inputMap->keyDownMappings);

        MouseKeyBind_vector_lazy_clear(&inputMap->mouseButtonUpMappings);
        MouseKeyBind_vector_lazy_clear(&inputMap->mouseButtonDownMappings);
}

void INP_parseInputs(SDL_Event* sdlEvent, struct INP_InputMap* inputMap,
                     struct Event_Vector* eventManager) {
        size_t keyDownVecLength =
            KeyBind_vector_size(&inputMap->keyDownMappings);
        size_t keyUpVecLength = KeyBind_vector_size(&inputMap->keyUpMappings);

        size_t mouseKeyDownVecLength =
            MouseKeyBind_vector_size(&inputMap->mouseButtonDownMappings);
        size_t mouseKeyUpVecLength =
            MouseKeyBind_vector_size(&inputMap->mouseButtonDownMappings);

        while (SDL_PollEvent(sdlEvent)) {
                // changes the button states (mouse and keyboard)
                switch (sdlEvent->type) {
                        case SDL_KEYDOWN:
                                for (size_t i = 0; i < keyDownVecLength; ++i) {
                                        if (sdlEvent->key.keysym.scancode ==
                                            KeyBind_vector_get(
                                                &inputMap->keyDownMappings, i)
                                                .sdlKey)
                                                Event_vector_push_back(
                                                    eventManager,
                                                    KeyBind_vector_get(
                                                        &inputMap
                                                             ->keyDownMappings,
                                                        i)
                                                        .gameEvent);
                                }
                                break;

                        case SDL_KEYUP:
                                for (size_t i = 0; i < keyUpVecLength; ++i) {
                                        if (sdlEvent->key.keysym.scancode ==
                                            KeyBind_vector_get(
                                                &inputMap->keyUpMappings, i)
                                                .sdlKey)
                                                Event_vector_push_back(
                                                    eventManager,
                                                    KeyBind_vector_get(
                                                        &inputMap
                                                             ->keyUpMappings,
                                                        i)
                                                        .gameEvent);
                                }
                                break;

                        case SDL_MOUSEBUTTONDOWN:
                                for (size_t i = 0; i < mouseKeyDownVecLength;
                                     ++i) {
                                        if (sdlEvent->button.button ==
                                            MouseKeyBind_vector_get(
                                                &inputMap
                                                     ->mouseButtonDownMappings,
                                                i)
                                                .button)
                                                Event_vector_push_back(
                                                    eventManager,
                                                    MouseKeyBind_vector_get(
                                                        &inputMap
                                                             ->mouseButtonDownMappings,
                                                        i)
                                                        .gameEvent);
                                }
                                break;

                        case SDL_MOUSEBUTTONUP:
                                for (size_t i = 0; i < mouseKeyUpVecLength;
                                     ++i) {
                                        if (sdlEvent->button.button ==
                                            MouseKeyBind_vector_get(
                                                &inputMap
                                                     ->mouseButtonUpMappings,
                                                i)
                                                .button)
                                                Event_vector_push_back(
                                                    eventManager,
                                                    MouseKeyBind_vector_get(
                                                        &inputMap
                                                             ->mouseButtonUpMappings,
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
                                globalMouseState.scroll_direction =
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

void ECS_free_InputMap(struct INP_InputMap* inputMap) {
        KeyBind_vector_free(&inputMap->keyUpMappings);
        KeyBind_vector_free(&inputMap->keyDownMappings);

        MouseKeyBind_vector_free(&inputMap->mouseButtonUpMappings);
        MouseKeyBind_vector_free(&inputMap->mouseButtonDownMappings);
}
// -----------------------------------------
//    Macro definitions
// -----------------------------------------

VECTOR_DEFINE(struct INP_KeyBind, KeyBind)
VECTOR_DEFINE(struct INP_MouseKeyBind, MouseKeyBind)
