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
// a proper way to create a FreeList that holds ints:
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

#define FREELIST_DATA_DECLARE(STRUCT_NAME, DATATYPE, DATA_NAME) \
        struct STRUCT_NAME;                                     \
        struct STRUCT_NAME {                                    \
                DATATYPE DATA_NAME;                             \
                size_t next_free_index;                         \
        };

#define FREELIST_DECLARE(TYPE, PREFIX)                                         \
        /* Types... */                                                         \
        /* --------------------- */                                            \
                                                                               \
        struct PREFIX##_FreeList;                                              \
        struct PREFIX##_FreeList {                                             \
                struct PREFIX##_Vector data;                                   \
                size_t cur_free_index;                                         \
        };                                                                     \
                                                                               \
        /* Procedures... */                                                    \
        /* --------------------- */                                            \
                                                                               \
        /* freelist_init */                                                    \
        /* initializes a new freelist. Sets the current free index to 0*/      \
        void PREFIX##_freelist_init(struct PREFIX##_FreeList*);                \
                                                                               \
        /* freelist_reserve */                                                 \
        /* wrapper for vector_reserve.  Sets the new capacity elements to have \
         * the next proper free index */                                       \
        void PREFIX##_freelist_reserve(struct PREFIX##_FreeList*,              \
                                       const size_t);                          \
                                                                               \
        /* freelist_add */                                                     \
        /* adds an element to the first free spot on the free list. If the     \
         * vector is too small, the vector will reallocate. Also, returns the  \
         * position it added the element at.*/                                 \
        size_t PREFIX##_freelist_add(struct PREFIX##_FreeList*, const TYPE);   \
                                                                               \
        /* freelist_get */                                                     \
        /* gets an element at a given index. WARNING: does not do bounds       \
         * checking*/                                                          \
        TYPE PREFIX##_freelist_get(struct PREFIX##_FreeList*, const size_t);   \
                                                                               \
        /* freelist_removeat */                                                \
        /* removes an element at a given index by appending it to the          \
         * free_elements stack. Note: the index of the data will not change,   \
         * however, it will be overwritten next freelist_add. It will also NOT \
         * check if the data is already deleted*/                              \
        void PREFIX##_freelist_removeat(struct PREFIX##_FreeList*,             \
                                        const size_t);                         \
                                                                               \
        /* freelist_free */                                                    \
        /* frees the free list's memory */                                     \
        void PREFIX##_freelist_free(struct PREFIX##_FreeList*);

#define FREELIST_DEFINE(TYPE, PREFIX)                                       \
        /* freelist_init */                                                 \
        void PREFIX##_freelist_init(struct PREFIX##_FreeList* freelist) {   \
                struct PREFIX##_Vector vec;                                 \
                PREFIX##_vector_init(&vec);                                 \
                freelist->data = vec;                                       \
                freelist->cur_free_index = 0;                               \
        }                                                                   \
                                                                            \
        /* freelist_reserve */                                              \
        void PREFIX##_freelist_reserve(struct PREFIX##_FreeList* freelist,  \
                                       const size_t new_capacity) {         \
                PREFIX##_vector_reserve(&freelist->data, new_capacity);     \
                TYPE tmp;                                                   \
                                                                            \
                for (size_t i = PREFIX##_vector_size(&freelist->data) + 1;  \
                     i <= new_capacity; ++i) {                              \
                        tmp.next_free_index = i;                            \
                        PREFIX##_vector_push_back(&freelist->data, tmp);    \
                }                                                           \
        }                                                                   \
                                                                            \
        /* freelist_add */                                                  \
        size_t PREFIX##_freelist_add(struct PREFIX##_FreeList* freelist,    \
                                     const TYPE val) {                      \
                size_t cur_free_index_ = freelist->cur_free_index;          \
                /* if there are no empty nodes (when the cur_free_index is  \
                 * equal to the vector's size) reallocate appropriately */  \
                if (cur_free_index_ ==                                      \
                    PREFIX##_vector_size(&freelist->data)) {                \
                        PREFIX##_freelist_reserve(                          \
                            freelist,                                       \
                            PREFIX##_vector_size(&freelist->data) * 1.5);   \
                }                                                           \
                size_t next_free_index_ =                                   \
                    PREFIX##_vector_get(&freelist->data, cur_free_index_)   \
                        .next_free_index;                                   \
                                                                            \
                PREFIX##_vector_set(&freelist->data, cur_free_index_, val); \
                                                                            \
                freelist->cur_free_index = next_free_index_;                \
                                                                            \
                return cur_free_index_;                                     \
        }                                                                   \
                                                                            \
        /* freelist_get */                                                  \
        TYPE PREFIX##_freelist_get(struct PREFIX##_FreeList* freelist,      \
                                   const size_t index) {                    \
                return PREFIX##_vector_get(&freelist->data, index);         \
        }                                                                   \
                                                                            \
        /* freelist_removeat */                                             \
        void PREFIX##_freelist_removeat(struct PREFIX##_FreeList* freelist, \
                                        const size_t index) {               \
                TYPE tmp = PREFIX##_vector_get(&freelist->data, index);     \
                tmp.next_free_index = freelist->cur_free_index;             \
                PREFIX##_vector_set(&freelist->data, index, tmp);           \
                freelist->cur_free_index = index;                           \
        }                                                                   \
                                                                            \
        /* freelist_free */                                                 \
        void PREFIX##_freelist_free(struct PREFIX##_FreeList* freelist) {   \
                PREFIX##_vector_free(&freelist->data);                      \
        }
