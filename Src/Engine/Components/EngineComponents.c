#include "EngineComponents.h"
#include "stdint.h"

void ECS_initComponents(struct ECS_Components* engineComponents,
                        size_t capacity) {
        EFreeList_init(&engineComponents->free_elements);
        EFreeList_reserve(&engineComponents->free_elements, capacity);

        // initilizes all the components with capacity
#define X_CPT(type, name) \
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
#define X_CPT(type, name) \
        name##Manager_remove_at(&engineComponents->MANAGER_NAME(name), index);
        LIST_OF_COMPONENTS
#undef X_CPT
}

// defining the componenet managers
#define X_CPT(type, name)         \
        VECTOR_DEFINE(type, name) \
        COMPONENT_MANAGER_DEFINE(type, name, name)
LIST_OF_COMPONENTS
#undef X_CPT

// defining the component manager getters
#define X_CPT(type, name)                                     \
        struct name##Manager* MANAGER_GETTER_NAME(name)(      \
            struct ECS_Components * engineComponents) {       \
                return &engineComponents->MANAGER_NAME(name); \
        }
LIST_OF_COMPONENTS
#undef X_CPT

// ECS_add<name>At(components, index, val )
#define X_CPT(type, name)                                                     \
        void MANAGER_ADD_AT_NAME(name)(                                       \
            struct ECS_Components * engineComponents, size_t index,           \
            type * val) {                                                     \
                name##Manager_add_at(                                         \
                    MANAGER_GETTER_NAME(name)(engineComponents), index, val); \
        }
LIST_OF_COMPONENTS
#undef X_CPT

// ECS_add<name>(components, index, val )
#define X_CPT(type, name)                                               \
        void MANAGER_ADD_NAME(name)(struct ECS_Components * components, \
                                    type * val) {                       \
                MANAGER_ADD_AT_NAME(name)                               \
                (components, ECS_getCurFreeIndex(components), val);     \
        }
LIST_OF_COMPONENTS
#undef X_CPT

// free components
void ECS_freeComponents(struct ECS_Components* engineComponents) {
        EFreeList_free(&engineComponents->free_elements);

        // initilizes all the components with capacity
#define X_CPT(type, name) \
        name##Manager_free(&engineComponents->MANAGER_NAME(name));
        LIST_OF_COMPONENTS
#undef X_CPT
}
