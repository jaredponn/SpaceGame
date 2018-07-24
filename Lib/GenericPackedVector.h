#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "sizet_Vector.h"

/**
 * Macros for a generic packed vector. Before using this, ensure that you create
 a vector with the same TYPE and PREFIX as the PackedVector.
 *
 * Specifcations are as follows:
 * sparse_vector: sparse vector that contains indexes to the index of the data
 in the packed_vector
 * next_packed_index: maintains the state of where to put the next val
 * packed_indices: indicies that allow the reverse O(1) lookup of the
 sparse_vector index of a val in the packed_data
 * packed_data: packed array of data for iteration
 *
 * functions:
 * add -> O(1) and placed unsorted in a contigious memory packed_vector
 * deletion -> O(1) utilizes pop and swap to be O(1) whilst having contigous
 memory in the packed_data vector
 */

#define PACKEDVECTOR_DECLARE(TYPE, PREFIX)                                     \
        /* Types... */                                                         \
        /* --------------------- */                                            \
        struct PREFIX##_PackedVector;                                          \
        struct PREFIX##_PackedVector {                                         \
                struct sizet_Vector sparse_vector;                             \
                size_t next_packed_index; /* next empty index in the packed    \
                                             array */                          \
                struct sizet_Vector                                            \
                    packed_indices; /* index of the corrosponding packed_data  \
                            in the sparse_vector*/                             \
                                                                               \
                struct PREFIX##_Vector                                         \
                    packed_data; /* tightly packed array of the data */        \
        };                                                                     \
                                                                               \
        /* Procedures... */                                                    \
        /* --------------------- */                                            \
                                                                               \
        /* packedvector_init */                                                \
        /* initializes the packedvector with a given capcity. Fills the        \
         * sparse_vectorwith null values. */                                   \
        void PREFIX##_packedvector_init(                                       \
            struct PREFIX##_PackedVector* packedvector, size_t capacity);      \
                                                                               \
        /* packedvector_add_at */                                              \
        /* at "index" in "sparse_vector," a size_t will point to the "val" in  \
         * the tightly packed "packed_data" vector. Increases the              \
         * "next_packed_index" by 1 as well. WARNING: Does minor bounds        \
         * checking - if the desired index is out of bounds, it will realocate \
         * so the vector is 1.5x the size of the required index. Also, it      \
         * checks to see if the current index is free, so it will not add to   \
         * the index UNLESS it is free.*/                                      \
        void PREFIX##_packedvector_add_at(                                     \
            struct PREFIX##_PackedVector* packedvector, const size_t index,    \
            TYPE* val);                                                        \
                                                                               \
        /* packedvector_remove_at */                                           \
        /* remove the component in the packed array "packed_data" by           \
         * vector_swap_back and vector_pop_back. Reduces "next_packed_index"   \
         * by 1 as well as sets the sparse_vector's "index" to size_t max to   \
         * denote that it no longer exists. It will not remove an index that   \
         * is already removed */                                               \
        void PREFIX##_packedvector_remove_at(                                  \
            struct PREFIX##_PackedVector* packedvector, size_t index);         \
                                                                               \
        /* packedvector_get_packed_data */                                     \
        /* returns a const pointer to the vector of the packed_data */         \
        const struct PREFIX##_Vector* PREFIX##_packedvector_get_packed_data(   \
            const struct PREFIX##_PackedVector* packedvector);                 \
                                                                               \
        /* packedvector_get_p_at */                                            \
        /* at index, it will return a pointerto the packed_data it corrosponds \
         * to. If it is out of bounds, or there is no data for that point, it  \
         * will return NULL. This allows the data to be modifed. "index"       \
         * refers to the sparse_vector that entity is known as */              \
        TYPE* PREFIX##_packedvector_get_p_at(                                  \
            struct PREFIX##_PackedVector* packedvector, size_t index);         \
                                                                               \
        /* packedvector_get_index_from */                                      \
        /* at "index" for the packed data vector(packed_data), it will return  \
         * the corrosponding sparse_vector index. WARNING: Does not do bounds  \
         * checking                                                            \
         * TODO WRITE UNIT TESTS FOR THIS                                      \
         */                                                                    \
        size_t PREFIX##_packedvector_get_index_from(                           \
            const struct PREFIX##_PackedVector* packedvector, size_t index);   \
                                                                               \
        /* packedvector_free */                                                \
        /* frees the PackedVector*/                                            \
        void PREFIX##_packedvector_free(                                       \
            struct PREFIX##_PackedVector* packedvector);

#define PACKEDVECTOR_DEFINE(TYPE, PREFIX)                                      \
        /* packedvector_init */                                                \
        void PREFIX##_packedvector_init(                                       \
            struct PREFIX##_PackedVector* packedvector, size_t capacity) {     \
                /* setting the sparse vector to the capacity with SIZE_MAX as  \
                 * the default value */                                        \
                sizet_vector_init(&packedvector->sparse_vector);               \
                sizet_vector_resize(&packedvector->sparse_vector, capacity,    \
                                    SIZE_MAX);                                 \
                                                                               \
                /*setting the next index to 0*/                                \
                packedvector->next_packed_index = 0;                           \
                                                                               \
                /* reserving the data for the global indices and data*/        \
                sizet_vector_init(&packedvector->packed_indices);              \
                sizet_vector_reserve(&packedvector->packed_indices, capacity); \
                                                                               \
                PREFIX##_vector_init(&packedvector->packed_data);              \
                PREFIX##_vector_reserve(&packedvector->packed_data, capacity); \
        }                                                                      \
                                                                               \
        /* packedvector_add_at */                                              \
        void PREFIX##_packedvector_add_at(                                     \
            struct PREFIX##_PackedVector* packedvector, const size_t index,    \
            TYPE* val) {                                                       \
                /* if the desired index is outside of the                      \
                 * sparse_vector, it                                           \
                 * will resize itself to be 1.5X the index */                  \
                if (index >=                                                   \
                    sizet_vector_capacity(&packedvector->sparse_vector)) {     \
                        sizet_vector_resize(&packedvector->sparse_vector,      \
                                            index * 1.5, SIZE_MAX);            \
                }                                                              \
                /*checks to see if it is actually a free index before adding   \
                 * the val to the packedvector*/                               \
                if (sizet_vector_get(&packedvector->sparse_vector, index) ==   \
                    SIZE_MAX) {                                                \
                        sizet_vector_set(&packedvector->sparse_vector, index,  \
                                         packedvector->next_packed_index);     \
                                                                               \
                        sizet_vector_push_back(&packedvector->packed_indices,  \
                                               index);                         \
                        PREFIX##_vector_push_back(&packedvector->packed_data,  \
                                                  *val);                       \
                        /* increases the next index by one, so that            \
                         * the next add will push_back */                      \
                        ++packedvector->next_packed_index;                     \
                }                                                              \
        }                                                                      \
                                                                               \
        /* packedvector_remove_at */                                           \
        void PREFIX##_packedvector_remove_at(                                  \
            struct PREFIX##_PackedVector* packedvector, size_t index) {        \
                /* ensures that we only remove free indicies */                \
                if (sizet_vector_get(&packedvector->sparse_vector, index) !=   \
                    SIZE_MAX) {                                                \
                        /*if there is only 1 index left, just pop_back it from \
                         * the vectors*/                                       \
                        if (sizet_vector_size(                                 \
                                &packedvector->packed_indices) == 1) {         \
                                /* setting the sparse_vector index to SIZE_MAX \
                                 */                                            \
                                sizet_vector_set(&packedvector->sparse_vector, \
                                                 index, SIZE_MAX);             \
                                                                               \
                                /* Popping the unused data at the end of the   \
                                 * densely packed vectors */                   \
                                sizet_vector_pop_back(                         \
                                    &packedvector->packed_indices);            \
                                PREFIX##_vector_pop_back(                      \
                                    &packedvector->packed_data);               \
                        } else {                                               \
                                size_t lastSparseVectorIndex =                 \
                                    sizet_vector_get(                          \
                                        &packedvector->packed_indices,         \
                                        sizet_vector_size(                     \
                                            &packedvector->packed_indices) -   \
                                            1);                                \
                                                                               \
                                /*swapping the sparse vector */                \
                                sizet_vector_swap(                             \
                                    &packedvector->sparse_vector, index,       \
                                    lastSparseVectorIndex);                    \
                                                                               \
                                /* swapping the global indices and packed data \
                                 * vector*/                                    \
                                sizet_vector_swap_back(                        \
                                    &packedvector->packed_indices, index);     \
                                PREFIX##_vector_swap_back(                     \
                                    &packedvector->packed_data, index);        \
                                                                               \
                                /* setting the sparse_vector index to SIZE_MAX \
                                 */                                            \
                                sizet_vector_set(&packedvector->sparse_vector, \
                                                 index, SIZE_MAX);             \
                                                                               \
                                /* Popping the unused data at the end of the   \
                                 * densely packed vectors */                   \
                                sizet_vector_pop_back(                         \
                                    &packedvector->packed_indices);            \
                                PREFIX##_vector_pop_back(                      \
                                    &packedvector->packed_data);               \
                        }                                                      \
                        /* required so the add function works properly*/       \
                        --packedvector->next_packed_index;                     \
                }                                                              \
        }                                                                      \
                                                                               \
        /* packedvector_get_packed_data */                                     \
        const struct PREFIX##_Vector* PREFIX##_packedvector_get_packed_data(   \
            const struct PREFIX##_PackedVector* packedvector) {                \
                return &packedvector->packed_data;                             \
        }                                                                      \
                                                                               \
        /* packedvector_get_p_at */                                            \
        TYPE* PREFIX##_packedvector_get_p_at(                                  \
            struct PREFIX##_PackedVector* packedvector, size_t index) {        \
                if (index >=                                                   \
                        sizet_vector_size(&packedvector->sparse_vector) ||     \
                    sizet_vector_get(&packedvector->sparse_vector, index) ==   \
                        SIZE_MAX) {                                            \
                        return NULL;                                           \
                } else {                                                       \
                        size_t dataIndex = sizet_vector_get(                   \
                            &packedvector->sparse_vector, index);              \
                        return packedvector->packed_data.data + dataIndex;     \
                }                                                              \
        }                                                                      \
                                                                               \
        /* packedvector_get_index_from */                                      \
        size_t PREFIX##_packedvector_get_index_from(                           \
            const struct PREFIX##_PackedVector* packedvector, size_t index) {  \
                return sizet_vector_get(&packedvector->packed_indices, index); \
        }                                                                      \
                                                                               \
        /* packedvector_free */                                                \
        /* frees the data in the packedvectors*/                               \
        void PREFIX##_packedvector_free(                                       \
            struct PREFIX##_PackedVector* packedvector) {                      \
                sizet_vector_free(&packedvector->sparse_vector);               \
                sizet_vector_free(&packedvector->packed_indices);              \
                PREFIX##_vector_free(&packedvector->packed_data);              \
        }
