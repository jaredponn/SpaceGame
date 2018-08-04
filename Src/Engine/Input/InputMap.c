#include "InputMap.h"
// -----------------------------------------
//    Constants
// -----------------------------------------

#define NUM_OF_KEYBOARD_KEYS 284
#define NUM_OF_MOUSE_BUTTONS 6

// -----------------------------------------
//    private func declarations
// -----------------------------------------

static inline void INP_addKeyBinding(struct KeyBindVector *,
				     const struct INP_KeyBind *);
static inline void INP_addMouseKeyBinding(struct MouseKeyBindVector *,
					  const struct INP_MouseKeyBind *);


// -----------------------------------------
//    implementations
// -----------------------------------------

void INP_initInputMap(struct INP_InputMap *inputMap)
{
	// initlizing the vectors
	KeyBindVector_init(&inputMap->keyPressMappings);
	KeyBindVector_init(&inputMap->keyReleaseMappings);

	KeyBindVector_reserve(&inputMap->keyPressMappings,
			      NUM_OF_KEYBOARD_KEYS);
	KeyBindVector_reserve(&inputMap->keyReleaseMappings,
			      NUM_OF_KEYBOARD_KEYS);

	MouseKeyBindVector_init(&inputMap->mouseButtonPressMappings);
	MouseKeyBindVector_init(&inputMap->mouseButtonReleaseMappings);
	MouseKeyBindVector_reserve(&inputMap->mouseButtonPressMappings,
				   NUM_OF_MOUSE_BUTTONS);
	MouseKeyBindVector_reserve(&inputMap->mouseButtonReleaseMappings,
				   NUM_OF_MOUSE_BUTTONS);

	inputMap->mouseMovementEvent = &EVT_VOIDFUNC;
	inputMap->mouseScrollEvent = &EVT_VOIDFUNC;
}

void INP_clearInputMap(struct INP_InputMap *inputMap)
{
	// initlizing the vectors
	KeyBindVector_lazy_clear(&inputMap->keyPressMappings);
	KeyBindVector_lazy_clear(&inputMap->keyReleaseMappings);

	MouseKeyBindVector_lazy_clear(&inputMap->mouseButtonPressMappings);
	MouseKeyBindVector_lazy_clear(&inputMap->mouseButtonReleaseMappings);
}

void ECS_freeInputMap(struct INP_InputMap *inputMap)
{
	KeyBindVector_free(&inputMap->keyPressMappings);
	KeyBindVector_free(&inputMap->keyReleaseMappings);

	MouseKeyBindVector_free(&inputMap->mouseButtonPressMappings);
	MouseKeyBindVector_free(&inputMap->mouseButtonReleaseMappings);
}

// -----------------------------------------
//    adding key bindings
// -----------------------------------------

void INP_addKeyReleaseBinding(struct INP_InputMap *inputMap,
			      const struct INP_KeyBind keyBind)
{
	INP_addKeyBinding(&inputMap->keyReleaseMappings, &keyBind);
}

void INP_addKeyPressBinding(struct INP_InputMap *inputMap,
			    const struct INP_KeyBind keyBind)
{
	INP_addKeyBinding(&inputMap->keyPressMappings, &keyBind);
}

void INP_addMouseKeyReleaseBinding(struct INP_InputMap *inputMap,
				   const struct INP_MouseKeyBind keyBind)
{
	INP_addMouseKeyBinding(&inputMap->mouseButtonReleaseMappings, &keyBind);
}

void INP_addMouseKeyPressBinding(struct INP_InputMap *inputMap,
				 const struct INP_MouseKeyBind keyBind)
{
	INP_addMouseKeyBinding(&inputMap->mouseButtonPressMappings, &keyBind);
}

void INP_setMouseMovementEvent(struct INP_InputMap *inputMap,
			       EVT_GameEventEffect gameEventFunc)
{
	inputMap->mouseMovementEvent = gameEventFunc;
}
void INP_setMouseScrollEvent(struct INP_InputMap *inputMap,
			     EVT_GameEventEffect gameEventFunc)
{
	inputMap->mouseScrollEvent = gameEventFunc;
}

// -----------------------------------------
//    Macro definitions
// -----------------------------------------

VECTOR_DEFINE(struct INP_KeyBind, KeyBind)
VECTOR_DEFINE(struct INP_MouseKeyBind, MouseKeyBind)

// -----------------------------------------
//    Private function implementaitons
// -----------------------------------------

static inline void INP_addKeyBinding(struct KeyBindVector *vec,
				     const struct INP_KeyBind *keyBind)
{
	size_t vecLength = KeyBindVector_size(vec);

	struct INP_KeyBind *curKey_p = NULL;

	for (size_t i = 0; i < vecLength; ++i) {
		curKey_p = KeyBindVector_get_p(vec, i);

		if (keyBind->sdlKey == curKey_p->sdlKey) {
			printf("warning - replacing existing binding");
			curKey_p->sdlKey = keyBind->sdlKey;
			return;
		}
	}

	KeyBindVector_push_back(vec, *keyBind);
}

static inline void
INP_addMouseKeyBinding(struct MouseKeyBindVector *vec,
		       const struct INP_MouseKeyBind *keyBind)
{
	size_t vecLength = MouseKeyBindVector_size(vec);

	struct INP_MouseKeyBind *curKey_p = NULL;

	for (size_t i = 0; i < vecLength; ++i) {
		curKey_p = MouseKeyBindVector_get_p(vec, i);

		if (keyBind->sdlButton == curKey_p->sdlButton) {
			printf("warning - replacing existing binding");
			curKey_p->sdlButton = keyBind->sdlButton;
			return;
		}
	}

	MouseKeyBindVector_push_back(vec, *keyBind);
}
