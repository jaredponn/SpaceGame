#include "GameInputMaps.h"
#include "../EventManager/EventManager.h"

void INP_setDefaultMap(struct INP_InputMap* inputMap) {
        INP_clearInputMap(inputMap);

        INP_addKeyReleaseBinding(
            inputMap,
            ((struct INP_KeyBind){.sdlKey = SDL_SCANCODE_A,
                                  .gameEvent = (Event){.type = EVT_Spawn}}));
}
