#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "sizet_Vector.h"

/**
 * Macros for a generic component manager with add, and remove fucntions. To use
 * this, ensure that you create a vector with the same _TYPE and same _PREFIX as
 * the component manager.
 */

#define COMPONENT_MANAGER_DECLARE(_TYPE, _PREFIX)                              \
        /* Types... */                                                         \
        /* --------------------- */                                            \
        struct _PREFIX##_Manager;                                              \
        struct _PREFIX##_Manager {                                             \
                struct sizet_Vector sparse_vector;                             \
                size_t next_packed_index; /* next empty index in the packed    \
                                             array */                          \
                struct sizet_Vector                                            \
                    global_indices; /* index of the entity in the              \
                            entity manager. It is the global                   \
                            index that this particular entity                  \
                            is known as to the rest of the                     \
                            system. It matches vector "data"*/                 \
                                                                               \
                struct _PREFIX##_Vector                                        \
                    data; /* tightly packed array of the data */               \
        };                                                                     \
                                                                               \
        /* Procedures... */                                                    \
        /* --------------------- */                                            \
                                                                               \
        /* manager_init */                                                     \
        /* initializes the manager with a given capcity. Fills the             \
         * sparse_vectorwith null values. */                                   \
        void _PREFIX##_manager_init(struct _PREFIX##_Manager* manager,         \
                                    size_t capacity);                          \
                                                                               \
        /* manager_add_at */                                                   \
        /* at "index" in "sparse_vector," a size_t will point to the "val" in  \
         * the tightly packed "data" vector. Increases the "next_packed_index" \
         * by 1 as well. WARNING: Does minor bounds checking - if the desired  \
         * index is out of bounds, it will realocate so the vector is 1.5x the \
         * size of the required index. Also, it checks to see if the current   \
         * index is free, so it will not add to the index UNLESS it is free.*/ \
        void _PREFIX##_manager_add_at(struct _PREFIX##_Manager* manager,       \
                                      const size_t index, _TYPE val);          \
                                                                               \
        /* manager_remove */                                                   \
        /* remove the component in the packed array "data" by                  \
         * vector_swap_back and vector_pop_back. Reduces "next_packed_index"   \
         * by 1 as well as sets the sparse_vector's "index" to size_t max to   \
         * denote that it no longer exists. It will not remove an index that   \
         * is already removed */                                               \
        void _PREFIX##_manager_remove(struct _PREFIX##_Manager* manager,       \
                                      size_t index);                           \
                                                                               \
        /* manager_get_data_at */                                              \
        /* at index, it will return the data it corrosponds to. If it is out   \
         * of bounds, or there is no data for that point, it will return       \
         * NULL*/                                                              \
        _TYPE* _PREFIX##_manager_get_data_at(                                  \
            struct _PREFIX##_Manager* manager, size_t index);                  \
                                                                               \
        /* manager_free */                                                     \
        /* frees the data in the managers*/                                    \
        void _PREFIX##_manager_free(struct _PREFIX##_Manager* manager);

#define COMPONENT_MANAGER_DEFINE(_TYPE, _PREFIX)                               \
        /* manager_init */                                                     \
        void _PREFIX##_manager_init(struct _PREFIX##_Manager* manager,         \
                                    size_t capacity) {                         \
                /* setting the sparse vector to the capacity with SIZE_MAX as  \
                 * the default value */                                        \
                sizet_vector_init(&manager->sparse_vector);                    \
                sizet_vector_resize(&manager->sparse_vector, capacity,         \
                                    SIZE_MAX);                                 \
                sizet_vector_resize(&manager->sparse_vector, capacity,         \
                                    SIZE_MAX);                                 \
                                                                               \
                /*setting the next index to 0*/                                \
                manager->next_packed_index = 0;                                \
                                                                               \
                /* reserving the data for the global indices and data*/        \
                sizet_vector_init(&manager->global_indices);                   \
                sizet_vector_reserve(&manager->global_indices, capacity);      \
                _PREFIX##_vector_init(&manager->data);                         \
                _PREFIX##_vector_reserve(&manager->data, capacity);            \
        }                                                                      \
                                                                               \
        /* manager_add_at */                                                   \
        void _PREFIX##_manager_add_at(struct _PREFIX##_Manager* manager,       \
                                      const size_t index, _TYPE val) {         \
                /* if the desired index is outside of the                      \
                 * sparse_vector, it                                           \
                 * will resize itself to be 1.5X the index */                  \
                if (index >= sizet_vector_capacity(&manager->sparse_vector)) { \
                        sizet_vector_resize(&manager->sparse_vector,           \
                                            index * 1.5, SIZE_MAX);            \
                }                                                              \
                /*checks to see if it is actually a free index before adding   \
                 * the val to the manager*/                                    \
                if (sizet_vector_get(&manager->sparse_vector, index) ==        \
                    SIZE_MAX) {                                                \
                        sizet_vector_set(&manager->sparse_vector, index,       \
                                         manager->next_packed_index);          \
                        /* if the next_packed_index is the same as the data    \
                         * vector's size (or global indices which should be    \
                         * the same), then just push back the value to the     \
                         * array. Otherwise, use vector_set.*/                 \
                        sizet_vector_push_back(&manager->global_indices,       \
                                               index);                         \
                        _PREFIX##_vector_push_back(&manager->data, val);       \
                        /* increases the next index by one, so that            \
                         * the next add will push_back */                      \
                        ++(manager->next_packed_index);                        \
                }                                                              \
        }                                                                      \
                                                                               \
        /* manager_remove */                                                   \
        void _PREFIX##_manager_remove(struct _PREFIX##_Manager* manager,       \
                                      size_t index) {                          \
                /* ensures that we only remove free indicies */                \
                if (sizet_vector_get(&manager->sparse_vector, index) !=        \
                    SIZE_MAX) {                                                \
                        /*if there is only 1 index left, just pop_back it from \
                         * the vectors*/                                       \
                        if (sizet_vector_size(&manager->global_indices) ==     \
                            1) {                                               \
                                /* setting the sparse_vector index to SIZE_MAX \
                                 */                                            \
                                sizet_vector_set(&manager->sparse_vector,      \
                                                 index, SIZE_MAX);             \
                                                                               \
                                /* Popping the unused data at the end of the   \
                                 * densely packed vectors */                   \
                                sizet_vector_pop_back(                         \
                                    &manager->global_indices);                 \
                                _PREFIX##_vector_pop_back(&manager->data);     \
                        } else {                                               \
                                size_t lastSparseVectorIndex =                 \
                                    sizet_vector_get(                          \
                                        &manager->global_indices,              \
                                        sizet_vector_size(                     \
                                            &manager->global_indices) -        \
                                            1);                                \
                                                                               \
                                /*swapping the sparse vector */                \
                                sizet_vector_swap(&manager->sparse_vector,     \
                                                  index,                       \
                                                  lastSparseVectorIndex);      \
                                                                               \
                                /* swapping the global indices and packed data \
                                 * vector*/                                    \
                                sizet_vector_swap_back(                        \
                                    &manager->global_indices, index);          \
                                _PREFIX##_vector_swap_back(&manager->data,     \
                                                           index);             \
                                                                               \
                                /* setting the sparse_vector index to SIZE_MAX \
                                 */                                            \
                                sizet_vector_set(&manager->sparse_vector,      \
                                                 index, SIZE_MAX);             \
                                                                               \
                                /* Popping the unused data at the end of the   \
                                 * densely packed vectors */                   \
                                sizet_vector_pop_back(                         \
                                    &manager->global_indices);                 \
                                _PREFIX##_vector_pop_back(&manager->data);     \
                        }                                                      \
                        /* required so the add function works properly*/       \
                        --(manager->next_packed_index);                        \
                }                                                              \
        }                                                                      \
                                                                               \
        /* manager_get_data_at */                                              \
        /* at index, it will return a pointer to the data it corrosponds to.   \
         * If it is out of bounds, or there is no data for that point, it will \
         * return NULL*/                                                       \
        _TYPE* _PREFIX##_manager_get_data_at(                                  \
            struct _PREFIX##_Manager* manager, size_t index) {                 \
                if (index >= sizet_vector_size(&manager->sparse_vector) ||     \
                    sizet_vector_get(&manager->sparse_vector, index) ==        \
                        SIZE_MAX) {                                            \
                        return NULL;                                           \
                } else {                                                       \
                        size_t dataIndex =                                     \
                            sizet_vector_get(&manager->sparse_vector, index);  \
                        return manager->data.data + dataIndex;                 \
                }                                                              \
        }                                                                      \
                                                                               \
        /* manager_free */                                                     \
        /* frees the data in the managers*/                                    \
        void _PREFIX##_manager_free(struct _PREFIX##_Manager* manager) {       \
                sizet_vector_free(&manager->sparse_vector);                    \
                sizet_vector_free(&manager->global_indices);                   \
                _PREFIX##_vector_free(&manager->data);                         \
        }