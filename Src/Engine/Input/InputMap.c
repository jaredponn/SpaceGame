#include "InputMap.h"
// -----------------------------------------
//    Constants
// -----------------------------------------

#define NUM_OF_KEYBOARD_KEYS 284
#define NUM_OF_MOUSE_BUTTONS 6

// -----------------------------------------
//    private func declarations
// -----------------------------------------

static void INP_addKeyBinding(struct KeyBind_Vector*,
                              const struct INP_KeyBind*);
static void INP_addMouseKeyBinding(struct MouseKeyBind_Vector*,
                                   const struct INP_MouseKeyBind*);

// -----------------------------------------
//    implementations
// -----------------------------------------

void INP_initInputMap(struct INP_InputMap* inputMap) {
        // initlizing the vectors
        KeyBind_vector_init(&inputMap->keyPressMappings);
        KeyBind_vector_init(&inputMap->keyReleaseMappings);

        KeyBind_vector_reserve(&inputMap->keyPressMappings,
                               NUM_OF_KEYBOARD_KEYS);
        KeyBind_vector_reserve(&inputMap->keyReleaseMappings,
                               NUM_OF_KEYBOARD_KEYS);

        MouseKeyBind_vector_init(&inputMap->mouseButtonPressMappings);
        MouseKeyBind_vector_init(&inputMap->mouseButtonReleaseMappings);
        MouseKeyBind_vector_reserve(&inputMap->mouseButtonPressMappings,
                                    NUM_OF_MOUSE_BUTTONS);
        MouseKeyBind_vector_reserve(&inputMap->mouseButtonReleaseMappings,
                                    NUM_OF_MOUSE_BUTTONS);

        inputMap->mouseMovementEvent = (Event){.type = EVT_Empty};
        inputMap->mouseScrollEvent = (Event){.type = EVT_Empty};
}

void INP_clearInputMap(struct INP_InputMap* inputMap) {
        // initlizing the vectors
        KeyBind_vector_lazy_clear(&inputMap->keyPressMappings);
        KeyBind_vector_lazy_clear(&inputMap->keyReleaseMappings);

        MouseKeyBind_vector_lazy_clear(&inputMap->mouseButtonPressMappings);
        MouseKeyBind_vector_lazy_clear(&inputMap->mouseButtonReleaseMappings);
}

void ECS_freeInputMap(struct INP_InputMap* inputMap) {
        KeyBind_vector_free(&inputMap->keyPressMappings);
        KeyBind_vector_free(&inputMap->keyReleaseMappings);

        MouseKeyBind_vector_free(&inputMap->mouseButtonPressMappings);
        MouseKeyBind_vector_free(&inputMap->mouseButtonReleaseMappings);
}

// -----------------------------------------
//    adding key bindings
// -----------------------------------------

void INP_addKeyReleaseBinding(struct INP_InputMap* inputMap,
                              const struct INP_KeyBind keyBind) {
        INP_addKeyBinding(&inputMap->keyReleaseMappings, &keyBind);
}

void INP_addKeyPressBinding(struct INP_InputMap* inputMap,
                            const struct INP_KeyBind keyBind) {
        INP_addKeyBinding(&inputMap->keyPressMappings, &keyBind);
}

void INP_addMouseKeyReleaseBinding(struct INP_InputMap* inputMap,
                                   const struct INP_MouseKeyBind keyBind) {
        INP_addMouseKeyBinding(&inputMap->mouseButtonReleaseMappings, &keyBind);
}

void INP_addMouseKeyPressBinding(struct INP_InputMap* inputMap,
                                 const struct INP_MouseKeyBind keyBind) {
        INP_addMouseKeyBinding(&inputMap->mouseButtonPressMappings, &keyBind);
}

void INP_setMouseMovementEvent(struct INP_InputMap* inputMap, Event event) {
        inputMap->mouseMovementEvent = event;
}
void INP_setMouseScrollEvent(struct INP_InputMap* inputMap, Event event) {
        inputMap->mouseScrollEvent = event;
}

// -----------------------------------------
//    Macro definitions
// -----------------------------------------

VECTOR_DEFINE(struct INP_KeyBind, KeyBind)
VECTOR_DEFINE(struct INP_MouseKeyBind, MouseKeyBind)

// -----------------------------------------
//    Private function implementaitons
// -----------------------------------------

static void INP_addKeyBinding(struct KeyBind_Vector* vec,
                              const struct INP_KeyBind* keyBind) {
        size_t vecLength = KeyBind_vector_size(vec);

        struct INP_KeyBind* curKey_p = NULL;

        for (size_t i = 0; i < vecLength; ++i) {
                curKey_p = KeyBind_vector_get_p(vec, i);

                if (keyBind->sdlKey == curKey_p->sdlKey) {
                        curKey_p->sdlKey = keyBind->sdlKey;
                        return;
                }
        }

        KeyBind_vector_push_back(vec, *keyBind);
}

static void INP_addMouseKeyBinding(struct MouseKeyBind_Vector* vec,
                                   const struct INP_MouseKeyBind* keyBind) {
        size_t vecLength = MouseKeyBind_vector_size(vec);

        struct INP_MouseKeyBind* curKey_p = NULL;

        for (size_t i = 0; i < vecLength; ++i) {
                curKey_p = MouseKeyBind_vector_get_p(vec, i);

                if (keyBind->sdlButton == curKey_p->sdlButton) {
                        curKey_p->sdlButton = keyBind->sdlButton;
                        return;
                }
        }

        MouseKeyBind_vector_push_back(vec, *keyBind);
}
