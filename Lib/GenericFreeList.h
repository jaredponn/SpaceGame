#pragma once

#include <stdlib.h>
#include "GenericVector.h"
#include "Util.h"
/**
 * Declarations for a generic free list structure
 */
// NOTE: ensure that you declare a vector of structs with a field named: data,
// and next_free_index. Ensure that this has the same type TYPE and PREFIX as
// the freelist to ensure it works properly. For example, the following would be
// a proper way to create a FreeList that holds ints: OUTDATED TODO
/*
   struct FL_int {
        int myData; // this is the data that we want
        size_t next_free_index; // this is a must have for the free list to work
   };

   // Note: there is a wrapper to replicate the above behaviour with the
   following macro:

   FREELIST_DATA_DECLARE(FL_int, int, myData)

   VECTOR_DECLARE(struct FL_int, FL_int)
   VECTOR_DEFINE(struct FL_int, FL_int)

   FREELIST_DECLARE(struct FL_int, FL_int)
   FREELIST_DEFINE(struct FL_int, FL_int)

 */

#define FREELIST_DECLARE(TYPE, PREFIX, VECPREFIX) \
        FREELIST_TYPE_DECLARE(TYPE, PREFIX##FreeList, VECPREFIX)

#define FREELIST_DEFINE(TYPE, PREFIX, VECPREFIX) \
        FREELIST_TYPE_DEFINE(TYPE, PREFIX##FreeList, VECPREFIX)

#define FREELIST_TYPE_DECLARE(TYPE, NAME, VECPREFIX)                           \
        /* Types... */                                                         \
        /* --------------------- */                                            \
                                                                               \
        struct NAME;                                                           \
        struct NAME {                                                          \
                struct VECPREFIX##Vector data;                                 \
                size_t cur_free_index;                                         \
        };                                                                     \
                                                                               \
        /* Procedures... */                                                    \
        /* --------------------- */                                            \
                                                                               \
        /* freelist_init */                                                    \
        /* initializes a new freelist. Sets the current free index to 0*/      \
        void NAME##_init(struct NAME*);                                        \
                                                                               \
        /* freelist_reserve */                                                 \
        /* wrapper for vector_reserve.  Sets the new capacity elements to have \
         * the next proper free index */                                       \
        void NAME##_reserve(struct NAME*, const size_t);                       \
                                                                               \
        /* freelist_add */                                                     \
        /* adds an element to the first free spot on the free list. If the     \
         * vector is too small, the vector will reallocate. Also, returns the  \
         * position it added the element at.*/                                 \
        size_t NAME##_add(struct NAME*, const TYPE);                           \
                                                                               \
        /* freelist_get */                                                     \
        /* gets an element at a given index. WARNING: does not do bounds       \
         * checking*/                                                          \
        TYPE NAME##_get(struct NAME*, const size_t);                           \
                                                                               \
        /* freelist_get_curr_free_index */                                     \
        /* gets thecurrentfree index*/                                         \
        size_t NAME##_get_curr_free_index(struct NAME*);                       \
                                                                               \
        /* freelist_removeat */                                                \
        /* removes an element at a given index by appending it to the          \
         * free_elements stack. Note: the index of the data will not change,   \
         * however, it will be overwritten next freelist_add. It will also NOT \
         * check if the data is already deleted*/                              \
        void NAME##_remove_at(struct NAME*, const size_t);                     \
                                                                               \
        /* freelist_free */                                                    \
        /* frees the free list's memory */                                     \
        void NAME##_free(struct NAME*);

#define FREELIST_TYPE_DEFINE(TYPE, NAME, VECPREFIX)                           \
        /* freelist_init */                                                   \
        void NAME##_init(struct NAME* freelist) {                             \
                struct VECPREFIX##Vector vec;                                 \
                VECPREFIX##Vector_init(&vec);                                 \
                freelist->data = vec;                                         \
                freelist->cur_free_index = 0;                                 \
        }                                                                     \
                                                                              \
        /* freelist_reserve */                                                \
        void NAME##_reserve(struct NAME* freelist,                            \
                            const size_t new_capacity) {                      \
                VECPREFIX##Vector_reserve(&freelist->data, new_capacity);     \
                TYPE tmp;                                                     \
                                                                              \
                for (size_t i = VECPREFIX##Vector_size(&freelist->data) + 1;  \
                     i <= new_capacity; ++i) {                                \
                        tmp.next_free_index = i;                              \
                        VECPREFIX##Vector_push_back(&freelist->data, tmp);    \
                }                                                             \
        }                                                                     \
                                                                              \
        /* freelist_add */                                                    \
        size_t NAME##_add(struct NAME* freelist, const TYPE val) {            \
                size_t cur_free_index_ = freelist->cur_free_index;            \
                /* if there are no empty nodes (when the cur_free_index is    \
                 * equal to the vector's size) reallocate appropriately */    \
                if (cur_free_index_ ==                                        \
                    VECPREFIX##Vector_size(&freelist->data)) {                \
                        NAME##_reserve(                                       \
                            freelist,                                         \
                            VECPREFIX##Vector_size(&freelist->data) * 1.5);   \
                }                                                             \
                size_t next_free_index_ =                                     \
                    VECPREFIX##Vector_get(&freelist->data, cur_free_index_)   \
                        .next_free_index;                                     \
                                                                              \
                VECPREFIX##Vector_set(&freelist->data, cur_free_index_, val); \
                                                                              \
                freelist->cur_free_index = next_free_index_;                  \
                                                                              \
                return cur_free_index_;                                       \
        }                                                                     \
                                                                              \
        /* freelist_get */                                                    \
        TYPE NAME##_get(struct NAME* freelist, const size_t index) {          \
                return VECPREFIX##Vector_get(&freelist->data, index);         \
        }                                                                     \
                                                                              \
        /* freelist_get_curr_free_index */                                    \
        size_t NAME##_get_curr_free_index(struct NAME* freelist) {            \
                return freelist->cur_free_index;                              \
        }                                                                     \
                                                                              \
        /* freelist_remove_at */                                              \
        void NAME##_remove_at(struct NAME* freelist, const size_t index) {    \
                TYPE tmp = VECPREFIX##Vector_get(&freelist->data, index);     \
                tmp.next_free_index = freelist->cur_free_index;               \
                VECPREFIX##Vector_set(&freelist->data, index, tmp);           \
                freelist->cur_free_index = index;                             \
        }                                                                     \
                                                                              \
        /* freelist_free */                                                   \
        void NAME##_free(struct NAME* freelist) {                             \
                VECPREFIX##Vector_free(&freelist->data);                      \
        }
