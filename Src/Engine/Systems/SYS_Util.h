#pragma once

// executes a FOREACH command for the data in a COMPONENT_Manager
#define FOREACH_M(                                                             \
    _MANAGER_PREFIX, /*prefix used for the componenet manager                  \
                        and the vector*/                                       \
    _MANAGER_P,      /*name of the pointer that is the component manager*/     \
    _DECLARATIONS, /*declarations of temporary variables before the for loop*/ \
    _ACTIONS)      /*actions that occur to each enttiy*/                       \
        do {                                                                   \
                const struct _MANAGER_PREFIX##_Vector* data                    \
        } while (0)\
