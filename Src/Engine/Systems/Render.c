#include "Render.h"

void SYS_renderCopyAppearance(SDL_Renderer* renderer,
                              const Appearance* appearance) {
        SDL_RenderCopyEx(renderer, appearance->texture, &appearance->srcrect,
                         &appearance->dstrect, appearance->angle, NULL,
                         SDL_FLIP_NONE);
}

void SYS_renderCopy(SDL_Renderer* renderer,
                    const struct Appearance_Manager* appearanceManager) {
        const struct Appearance_Vector* appVec_p =
            Appearance_manager_get_data(appearanceManager);

        size_t size = Appearance_vector_size(appVec_p);

        for (size_t i = 0; i < size; ++i) {
                SYS_renderCopyAppearance(renderer,
                                         Appearance_vector_get_p(appVec_p, i));
        }
}
