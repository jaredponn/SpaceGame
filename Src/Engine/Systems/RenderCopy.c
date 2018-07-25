#include "RenderCopy.h"
#include "Src/Engine/Components/Appearance.h"
// -----------------------------------------
//    Local functio declarations
// -----------------------------------------

// renders an appearance. Essentially a wrapper for SDL_RenderCopyEx, but
// assumes that we do not wish to flip to change the center of the object, nor
// flip it.
static void renderCopyAppearance(SDL_Renderer*, const Appearance*);

// -----------------------------------------
//    Public function implementations
// -----------------------------------------

void SYS_renderCopy(SDL_Renderer* renderer,
                    const struct AppearanceManager* appearanceManager) {
        const struct AppearanceVector* appVec_p =
            AppearanceManager_get_packed_data(appearanceManager);

        size_t size = AppearanceVector_size(appVec_p);

        for (size_t i = 0; i < size; ++i) {
                renderCopyAppearance(renderer,
                                     AppearanceVector_get_p(appVec_p, i));
        }
}

// -----------------------------------------
//    Local function implementations
// -----------------------------------------

static void renderCopyAppearance(SDL_Renderer* renderer,
                                 const Appearance* appearance) {
        SDL_RenderCopyEx(renderer, appearance->texture, &appearance->srcrect,
                         &appearance->dstrect, appearance->angle, NULL,
                         SDL_FLIP_NONE);
}
