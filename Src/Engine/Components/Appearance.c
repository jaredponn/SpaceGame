#include "Appearance.h"

VECTOR_DEFINE(Appearance, Appearance)

void initAppearanceManager(struct AppearanceManager* appearancesManager,
                           size_t capacity) {
        sizet_vector_init(&appearancesManager->id);
        sizet_vector_reserve(&appearancesManager->id, capacity);

        Appearance_vector_init(&appearancesManager->appearances);
        Appearance_vector_reserve(&appearancesManager->appearances, capacity);
}
