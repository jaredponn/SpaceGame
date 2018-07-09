#include "Entity.h"
#include <stdint.h>

VECTOR_DEFINE(Entity, Entity)

void Entity_manager_init(struct Entity_Manager* entityManager,
                         size_t capacity) {
        Entity_vector_init(&entityManager->entities);
        Entity_vector_reserve(&entityManager->entities, capacity);

        E_freelist_init(&entityManager->free_elements);
        E_freelist_reserve(&entityManager->free_elements, capacity);
}

size_t Entity_manager_add_new_entity(struct Entity_Manager* entityManager,
                                     const Entity newEntity) {
        size_t curFreeIndex =
            E_freelist_add(&entityManager->free_elements, (E){SIZE_MAX});
        Entity_vector_set(&entityManager->entities, curFreeIndex, newEntity);
        return curFreeIndex;
}

Entity Entity_manager_remove(struct Entity_Manager* entityManager,
                             const size_t index) {
        E_freelist_removeat(&entityManager->free_elements, index);
        return Entity_vector_get(&entityManager->entities, index);
}
