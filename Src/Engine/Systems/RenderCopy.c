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
                    const struct Appearance_Manager* appearanceManager) {
        const struct Appearance_Vector* appVec_p =
            Appearance_manager_get_data(appearanceManager);

        size_t size = Appearance_vector_size(appVec_p);

        for (size_t i = 0; i < size; ++i) {
                renderCopyAppearance(renderer,
                                     Appearance_vector_get_p(appVec_p, i));
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
