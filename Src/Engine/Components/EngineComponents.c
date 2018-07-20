#include "EngineComponents.h"
#include "stdint.h"

void ECS_initComponents(struct ECS_Components* engineComponents,
                        size_t capacity) {
        E_freelist_init(&engineComponents->free_elements);
        E_freelist_reserve(&engineComponents->free_elements, capacity);

        // initilizes all the components with capacity
#define X_CPT(name) \
        name##_manager_init(&engineComponents->MANAGER_NAME(name), capacity);
        LIST_OF_COMPONENTS
#undef X_CPT
}

size_t ECS_get_next_free_index(struct E_FreeList* freeElements) {
        return E_freelist_add(freeElements, (E){SIZE_MAX});
}

void ECS_delete_entity_at(struct ECS_Components* engineComponents,
                          size_t index) {
        // marking the index free for the next get_next_free_index function
        E_freelist_removeat(&engineComponents->free_elements, index);

        // deleting the components each of the managers
#define X_CPT(name) \
        name##_manager_remove(&engineComponents->MANAGER_NAME(name), index);
        LIST_OF_COMPONENTS
#undef X_CPT
}

// defining the componenet managers
#define X_CPT(name)               \
        VECTOR_DEFINE(name, name) \
        COMPONENT_MANAGER_DEFINE(name, name)
LIST_OF_COMPONENTS
#undef X_CPT

// defining the component manager getters
#define X_CPT(name)                                           \
        struct name##_Manager* MANAGER_GETTER_NAME(name)(     \
            struct ECS_Components * engineComponents) {       \
                return &engineComponents->MANAGER_NAME(name); \
        }
LIST_OF_COMPONENTS
#undef X_CPT

// defining the compoent manager adders
#define X_CPT(type)                                                          \
        void ECS_add_##type##_at(struct ECS_Components* engineComponents,    \
                                 type* val, size_t index) {                  \
                type##_manager_add_at(                                       \
                    ECS_get_##type##_manager(engineComponents), index, val); \
        }
LIST_OF_COMPONENTS
#undef X_CPT

// free components
void ECS_freeComponents(struct ECS_Components* engineComponents) {
        E_freelist_free(&engineComponents->free_elements);

        // initilizes all the components with capacity
#define X_CPT(name) name##_manager_free(&engineComponents->MANAGER_NAME(name));
        LIST_OF_COMPONENTS
#undef X_CPT
}
