#include "EngineComponents.h"
#include "stdint.h"

size_t ECS_get_next_free_index(struct E_FreeList* freeElements) {
        return E_freelist_add(freeElements, (E){SIZE_MAX});
}

void ECS_delete_entity_at(struct ECS_Components* components, size_t index) {
        // marking the index free for the next get_next_free_index function
        E_freelist_removeat(&components->free_elements, index);

        // deleeting the components each of the managers
        Entity_manager_remove(&components->entity_manager, index);
        Acceleration_manager_remove(&components->acceleration_manager, index);
        Velocity_manager_remove(&components->velocity_manager, index);
        Position_manager_remove(&components->position_manager, index);
        Appearance_manager_remove(&components->appearance_manager, index);
}
