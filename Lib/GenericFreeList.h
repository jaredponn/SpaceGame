#pragma once

#include <stdlib.h>
#include "GenericStack.h"
#include "GenericVector.h"
#include "Util.h"
/**
 * Declarations for a generic free list structure
 */

STACK_DECLARE(size_t, size)
STACK_DEFINE(size_t, size)

// NOTE: ensure that you declare a vector with the same _TYPE and _PREFIX as the
// freelist to ensure it works properly
#define FREELIST_DECLARE(_TYPE, _PREFIX)                                     \
        /* Types... */                                                       \
        /* --------------------- */                                          \
                                                                             \
        struct _PREFIX##_FreeList;                                           \
        struct _PREFIX##_FreeList {                                          \
                struct _PREFIX##_Vector data;                                \
                struct size_Stack free_elements;                             \
        };                                                                   \
                                                                             \
        /* Procedures... */                                                  \
        /* --------------------- */                                          \
                                                                             \
        /* freelist_init */                                                  \
        /* initializes a new freelist*/                                      \
        void _PREFIX##_freelist_init(struct _PREFIX##_FreeList*);            \
                                                                             \
        /* freelist_reserve */                                               \
        /* wrapper for vector_reserve. Should only be called after           \
         * initilization*/                                                   \
        void _PREFIX##_freelist_reserve(struct _PREFIX##_FreeList*, size_t); \
                                                                             \
        /* freelist_add */                                                   \
        /* adds an element to the first free spot on the free list. If the   \
         * vector is too small, the vector will reallocate*/                 \
        void _PREFIX##_freelist_add(struct _PREFIX##_FreeList*, _TYPE);      \
                                                                             \
        /* freelist_get */                                                   \
        /* gets an element at a given index. WARNING: does not do bounds     \
         * checking*/                                                        \
        _TYPE _PREFIX##_freelist_get(struct _PREFIX##_FreeList*, size_t);    \
                                                                             \
        /* freelist_removeat */                                              \
        /* removes an element at a given index by appending it to the        \
         * free_elements stack. Note: the index of the data will not change, \
         * however, it will be overwritten next freelist_add.*/              \
        void _PREFIX##_freelist_removeat(struct _PREFIX##_FreeList*, size_t);

#define FREELIST_DEFINE(_TYPE, _PREFIX)                                       \
        /* freelist_init */                                                   \
        void _PREFIX##_freelist_init(struct _PREFIX##_FreeList* freelist) {   \
                struct _PREFIX##_Vector vec;                                  \
                _PREFIX##_vector_init(&vec);                                  \
                freelist->data = vec;                                         \
                                                                              \
                struct size_Stack stack;                                      \
                size_stack_init(&stack);                                      \
                freelist->free_elements = stack;                              \
        }                                                                     \
                                                                              \
        /* freelist_reserve */                                                \
        void _PREFIX##_freelist_reserve(struct _PREFIX##_FreeList* freelist,  \
                                        size_t new_capacity) {                \
                _PREFIX##_vector_reserve(&freelist->data, new_capacity);      \
        }                                                                     \
                                                                              \
        /* freelist_add */                                                    \
        void _PREFIX##_freelist_add(struct _PREFIX##_FreeList* freelist,      \
                                    _TYPE val) {                              \
                /* if there are no empty nodes, just pushback val to the      \
                 * vector */                                                  \
                if (size_stack_size(&freelist->free_elements) == 0) {         \
                        _PREFIX##_vector_pushback(&freelist->data, val);      \
                } else {                                                      \
                        /* otherwise, fill the node up on the stack */        \
                        size_t empty_index =                                  \
                            size_stack_pop(&freelist->free_elements);         \
                        _PREFIX##_vector_set(&freelist->data, empty_index,    \
                                             val);                            \
                }                                                             \
        }                                                                     \
                                                                              \
        /* freelist_get */                                                    \
        _TYPE _PREFIX##_freelist_get(struct _PREFIX##_FreeList* freelist,     \
                                     size_t index) {                          \
                return _PREFIX##_vector_get(&freelist->data, index);          \
        }                                                                     \
                                                                              \
        /* freelist_removeat */                                               \
        void _PREFIX##_freelist_removeat(struct _PREFIX##_FreeList* freelist, \
                                         size_t index) {                      \
                size_stack_push(&freelist->free_elements, index);             \
        }
