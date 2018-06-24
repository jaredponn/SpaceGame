#pragma once

#include <stdlib.h>
#include "GenericVector.h"
#include "Util.h"
/**
 * Declarations for a generic free list structure
 */
// NOTE: ensure that you declare a vector of structs with a field named: data,
// and next_free_index. Ensure that this has the same type _TYPE and _PREFIX as
// the freelist to ensure it works properly. For example, the following would be
// a proper way to create a FreeList that holds ints:
/*
   struct FL_int {
        int myData; // this is the data that we want
        size_t next_free_index; // this is a must have for the free list to work
   };

   // Note: there is a wrapper to replicat ethe above behaviour with the
   following macro:

   FREELIST_DATA_DECLARE(FL_int, int, myData)

   VECTOR_DECLARE(struct FL_int, FL_int)
   VECTOR_DEFINE(struct FL_int, FL_int)

   FREELIST_DECLARE(struct FL_int, FL_int)
   FREELIST_DEFINE(struct FL_int, FL_int)

 */

#define FREELIST_DATA_DECLARE(_STRUCT_NAME, _DATA_TYPE, _DATA_NAME) \
        struct _STRUCT_NAME;                                        \
        struct _STRUCT_NAME {                                       \
                _DATA_TYPE DATA_NAME;                               \
                size_t next_free_index;                             \
        };

#define FREELIST_DECLARE(_TYPE, _PREFIX)                                       \
        /* Types... */                                                         \
        /* --------------------- */                                            \
                                                                               \
        struct _PREFIX##_FreeList;                                             \
        struct _PREFIX##_FreeList {                                            \
                struct _PREFIX##_Vector data;                                  \
                size_t cur_free_index;                                         \
        };                                                                     \
                                                                               \
        /* Procedures... */                                                    \
        /* --------------------- */                                            \
                                                                               \
        /* freelist_init */                                                    \
        /* initializes a new freelist. Sets the current free index to 0*/      \
        void _PREFIX##_freelist_init(struct _PREFIX##_FreeList*);              \
                                                                               \
        /* freelist_reserve */                                                 \
        /* wrapper for vector_reserve.  Sets the new capacity elements to have \
         * the next proper free index */                                       \
        void _PREFIX##_freelist_reserve(struct _PREFIX##_FreeList*, size_t);   \
                                                                               \
        /* freelist_add */                                                     \
        /* adds an element to the first free spot on the free list. If the     \
         * vector is too small, the vector will reallocate. Also, returns the  \
         * position it added the element at.*/                                 \
        size_t _PREFIX##_freelist_add(struct _PREFIX##_FreeList*, _TYPE);      \
                                                                               \
        /* freelist_get */                                                     \
        /* gets an element at a given index. WARNING: does not do bounds       \
         * checking*/                                                          \
        _TYPE _PREFIX##_freelist_get(struct _PREFIX##_FreeList*, size_t);      \
                                                                               \
        /* freelist_removeat */                                                \
        /* removes an element at a given index by appending it to the          \
         * free_elements stack. Note: the index of the data will not change,   \
         * however, it will be overwritten next freelist_add.*/                \
        void _PREFIX##_freelist_removeat(struct _PREFIX##_FreeList*, size_t);

#define FREELIST_DEFINE(_TYPE, _PREFIX)                                       \
        /* freelist_init */                                                   \
        void _PREFIX##_freelist_init(struct _PREFIX##_FreeList* freelist) {   \
                struct _PREFIX##_Vector vec;                                  \
                _PREFIX##_vector_init(&vec);                                  \
                freelist->data = vec;                                         \
                freelist->cur_free_index = 0;                                 \
        }                                                                     \
                                                                              \
        /* freelist_reserve */                                                \
        void _PREFIX##_freelist_reserve(struct _PREFIX##_FreeList* freelist,  \
                                        size_t new_capacity) {                \
                _PREFIX##_vector_reserve(&freelist->data, new_capacity);      \
                _TYPE tmp;                                                    \
                                                                              \
                for (size_t i = _PREFIX##_vector_size(&freelist->data) + 1;   \
                     i <= new_capacity; ++i) {                                \
                        tmp.next_free_index = i;                              \
                        _PREFIX##_vector_pushback(&freelist->data, tmp);      \
                }                                                             \
        }                                                                     \
                                                                              \
        /* freelist_add */                                                    \
        size_t _PREFIX##_freelist_add(struct _PREFIX##_FreeList* freelist,    \
                                      _TYPE val) {                            \
                size_t cur_free_index_ = freelist->cur_free_index;            \
                /* if there are no empty nodes (when the cur_free_index is    \
                 * equal to the vector's size) reallocate appropriately */    \
                if (cur_free_index_ ==                                        \
                    _PREFIX##_vector_size(&freelist->data)) {                 \
                        _PREFIX##_freelist_reserve(                           \
                            freelist,                                         \
                            _PREFIX##_vector_size(&freelist->data) * 1.5);    \
                }                                                             \
                size_t next_free_index_ =                                     \
                    _PREFIX##_vector_get(&freelist->data, cur_free_index_)    \
                        .next_free_index;                                     \
                                                                              \
                _PREFIX##_vector_set(&freelist->data, cur_free_index_, val);  \
                                                                              \
                freelist->cur_free_index = next_free_index_;                  \
                                                                              \
                return cur_free_index_;                                       \
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
                _TYPE tmp = _PREFIX##_vector_get(&freelist->data, index);     \
                tmp.next_free_index = freelist->cur_free_index;               \
                _PREFIX##_vector_set(&freelist->data, index, tmp);            \
                freelist->cur_free_index = index;                             \
        }
