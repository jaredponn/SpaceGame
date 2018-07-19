#include "Input.h"

#define NUM_OF_KEYS 284

// WRITE A FUNCTINO TO INITILIZE THE STATE

// -----------------------------------------
//    state
// -----------------------------------------

// Uint corrosponds to the a specific key's state: SDL_KEYDOWN or SDL_KEYUP
static Uint32 INP_keys_curr[NUM_OF_KEYS] = {0};
static Uint32 INP_keys_old[NUM_OF_KEYS] = {0};

// mouse
static struct INP_Mouse_State INP_mouse_state_curr;
static struct INP_Mouse_State INP_mouse_state_old;

// -----------------------------------------
//    Procedures
// -----------------------------------------
void INP_updateInputState(SDL_Event* e) {
        while (SDL_PollEvent(e)) {
                // update the mouse position
                INP_mouse_state_curr.mouse.position = (struct V2){
                    .x = (float)e->button.x, .y = (float)e->button.y};

                // changes the button states (mouse and keyboard)
                switch (e->type) {
                        case SDL_KEYDOWN:
                                INP_keys_curr[e->key.keysym.scancode] =
                                    SDL_KEYDOWN;
                                printf("Key press detected\n");
                                break;

                        case SDL_KEYUP:
                                INP_keys_curr[e->key.keysym.scancode] =
                                    SDL_KEYUP;
                                printf("Key release detected\n");
                                break;

                        case SDL_MOUSEBUTTONDOWN:
                                INP_mouse_state_curr.mouse.state = SDL_PRESSED;
                                INP_mouse_state_curr.mouse.button =
                                    e->button.button;
                                break;

                        case SDL_MOUSEBUTTONUP:
                                INP_mouse_state_curr.mouse.state = SDL_RELEASED;
                                INP_mouse_state_curr.mouse.button =
                                    e->button.button;
                                break;

                        case SDL_MOUSEWHEEL:
                                INP_mouse_state_curr.scroll.scroll_direction =
                                    (struct V2){.x = (float)e->wheel.x,
                                                .y = (float)e->wheel.y};
                                break;

                        default:
                                break;
                }
        }
}

void INP_updateOldState() {
        memcpy(INP_keys_old, INP_keys_curr, NUM_OF_KEYS);
        INP_mouse_state_old = INP_mouse_state_curr;
}

const Uint32* INP_getCurrKeys() { return INP_keys_curr; }

const struct INP_Mouse_State* INP_getCurrMouseState() {
        return &INP_mouse_state_curr;
}

bool INP_onKeyReleaseTap(SDL_Scancode key) {
        return (INP_keys_curr[key] == SDL_KEYUP &&
                INP_keys_old[key] == SDL_KEYDOWN);
}

bool INP_onKeyPressTap(SDL_Scancode key) {
        return (INP_keys_curr[key] == SDL_KEYDOWN &&
                INP_keys_old[key] == SDL_KEYUP);
}

bool INP_onMouseReleaseTap(Uint8 button) {
        return (INP_mouse_state_curr.mouse.button == button &&
                INP_mouse_state_curr.mouse.state == SDL_RELEASED &&
                INP_mouse_state_old.mouse.state == SDL_PRESSED);
}

bool INP_onMousePressTap(Uint8 button) {
        return (INP_mouse_state_curr.mouse.button == button &&
                INP_mouse_state_curr.mouse.state == SDL_PRESSED &&
                INP_mouse_state_old.mouse.state == SDL_RELEASED);
}

const struct V2* INP_getMousePosition() {
        return &INP_mouse_state_curr.mouse.position;
}

const struct V2* INP_getScroll() {
        return &INP_mouse_state_curr.scroll.scroll_direction;
}
