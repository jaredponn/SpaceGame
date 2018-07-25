#include "EngineComponents.h"
#include "stdint.h"

void ECS_initComponents(struct ECS_Components* engineComponents,
                        size_t capacity) {
        EFreeList_init(&engineComponents->free_elements);
        EFreeList_reserve(&engineComponents->free_elements, capacity);

        // initilizes all the components with capacity
#define X_CPT(name) \
        name##Manager_init(&engineComponents->MANAGER_NAME(name), capacity);
        LIST_OF_COMPONENTS
#undef X_CPT
}

size_t ECS_updateCurFreeIndex(struct ECS_Components* components) {
        return EFreeList_add(&components->free_elements, (E){SIZE_MAX});
}

size_t ECS_getCurFreeIndex(struct ECS_Components* components) {
        return EFreeList_get_curr_free_index(&components->free_elements);
}

void ECS_deleteEntityAt(struct ECS_Components* engineComponents, size_t index) {
        // marking the index free for the next get_next_free_index function
        EFreeList_remove_at(&engineComponents->free_elements, index);

        // deleting the components each of the managers
#define X_CPT(name) \
        name##Manager_remove_at(&engineComponents->MANAGER_NAME(name), index);
        LIST_OF_COMPONENTS
#undef X_CPT
}

// defining the componenet managers
#define X_CPT(name)               \
        VECTOR_DEFINE(name, name) \
        COMPONENT_MANAGER_DEFINE(name, name, name)
LIST_OF_COMPONENTS
#undef X_CPT

// defining the component manager getters
#define X_CPT(name)                                           \
        struct name##Manager* MANAGER_GETTER_NAME(name)(      \
            struct ECS_Components * engineComponents) {       \
                return &engineComponents->MANAGER_NAME(name); \
        }
LIST_OF_COMPONENTS
#undef X_CPT

// defining the compoent manager adders
#define X_CPT(type)                                                          \
        void ECS_add##type##At(struct ECS_Components* engineComponents,      \
                               type* val, size_t index) {                    \
                type##Manager_add_at(                                        \
                    ECS_get_##type##_manager(engineComponents), index, val); \
        }
LIST_OF_COMPONENTS
#undef X_CPT

// free components
void ECS_freeComponents(struct ECS_Components* engineComponents) {
        EFreeList_free(&engineComponents->free_elements);

        // initilizes all the components with capacity
#define X_CPT(name) name##Manager_free(&engineComponents->MANAGER_NAME(name));
        LIST_OF_COMPONENTS
#undef X_CPT
}
