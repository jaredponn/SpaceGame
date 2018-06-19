#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Util.h"

/**
 * Macros for a vector (a wrapper for a continious memory object). Not C++
 * standard compliant.
 */

#define VECTOR_DECLARE(_TYPE, _PREFIX)                                         \
        /* Types... */                                                         \
        /* --------------------- */                                            \
                                                                               \
        struct _PREFIX##_Vector;                                               \
        struct _PREFIX##_Vector {                                              \
                size_t size;     /* sizeof the current elements in use */      \
                size_t capacity; /*total memory available for x elements */    \
                _TYPE* data;     /* actual data*/                              \
        };                                                                     \
                                                                               \
        /* Procedures... */                                                    \
        /* --------------------- */                                            \
                                                                               \
        /* vector_init */                                                      \
        /* initializes a vector */                                             \
        void _PREFIX##_vector_init(struct _PREFIX##_Vector* vector);           \
                                                                               \
        /* vector_reserve */                                                   \
        /* increases (or decreases) the capacity of a vector to the given size \
         */                                                                    \
        void _PREFIX##_vector_reserve(struct _PREFIX##_Vector* vector,         \
                                      size_t new_capacity);                    \
                                                                               \
        /* vector_resize */                                                    \
        /* resizes the size and capacity of a vector to the given size, and    \
         * fills it with a default val "val"*/                                 \
        void _PREFIX##_vector_resize(struct _PREFIX##_Vector* vector,          \
                                     size_t new_size, _TYPE val);              \
                                                                               \
        /* vector_size */                                                      \
        /* gets the current size of the vector (number of elements actually    \
         * being used)*/                                                       \
        size_t _PREFIX##_vector_size(struct _PREFIX##_Vector* vector);         \
                                                                               \
        /* vector_capacity */                                                  \
        /* gets the current capacity of the vector */                          \
        size_t _PREFIX##_vector_capacity(struct _PREFIX##_Vector* vector);     \
                                                                               \
        /* vector_pushback */                                                  \
        /*appends something (val) to the end of the size of the vector and     \
         * increases the vector's size by one. If vectoris too small, it       \
         * reallocates the vector so that it is 1.5x the original size  */     \
        void _PREFIX##_vector_pushback(struct _PREFIX##_Vector* vector,        \
                                       _TYPE val);                             \
                                                                               \
        /* vector_set */                                                       \
        /*sets a specified index to a new value (val). WARNING: does not do    \
         * bounds checking */                                                  \
        void _PREFIX##_vector_set(struct _PREFIX##_Vector*, size_t index,      \
                                  _TYPE val);                                  \
                                                                               \
        /* vector_get */                                                       \
        /*gets the specified index of an element. WARNING does not do bounds   \
         * checking   */                                                       \
        _TYPE _PREFIX##_vector_get(struct _PREFIX##_Vector*, size_t index);    \
                                                                               \
        /* vector_remove */                                                    \
        /*removes an element from the vector at and index and shifts all       \
         * elements to the right of it back 1. Reduces the size of the vector  \
         * by one as well. WARNING does not do bounds checking   */            \
        void _PREFIX##_vector_remove(struct _PREFIX##_Vector*, size_t index);  \
                                                                               \
        /* vector_free */                                                      \
        /*frees the memory allocated by the vector.       */                   \
        void _PREFIX##_vector_free(struct _PREFIX##_Vector*);

#define VECTOR_DEFINE(_TYPE, _PREFIX)                                         \
        /*vector_init*/                                                       \
        void _PREFIX##_vector_init(struct _PREFIX##_Vector* vector) {         \
                vector->size = 0;                                             \
                vector->capacity = 0;                                         \
                vector->data = (_TYPE*)safe_malloc(0);                        \
        }                                                                     \
                                                                              \
        /*vector_reserve*/                                                    \
        void _PREFIX##_vector_reserve(struct _PREFIX##_Vector* vector,        \
                                      size_t new_capacity) {                  \
                _TYPE* new_data = (_TYPE*)realloc(                            \
                    vector->data, sizeof(_TYPE) * new_capacity);              \
                if (new_data == NULL) {                                       \
                        fprintf(stderr,                                       \
                                "Error: insufficient memory upon vector "     \
                                "allocation");                                \
                        exit(0);                                              \
                } else {                                                      \
                        vector->data = new_data;                              \
                        new_data = NULL;                                      \
                        vector->capacity = new_capacity;                      \
                }                                                             \
        }                                                                     \
                                                                              \
        /*vector_resize*/                                                     \
        void _PREFIX##_vector_resize(struct _PREFIX##_Vector* vector,         \
                                     size_t new_size, _TYPE val) {            \
                _PREFIX##_vector_reserve(vector, new_size);                   \
                for (size_t i = vector->size; i < vector->capacity; ++i) {    \
                        _PREFIX##_vector_set(vector, i, val);                 \
                }                                                             \
                vector->size = new_size;                                      \
                vector->capacity = new_size;                                  \
        }                                                                     \
                                                                              \
        /*vector_size*/                                                       \
        size_t _PREFIX##_vector_size(struct _PREFIX##_Vector* vector) {       \
                return vector->size;                                          \
        }                                                                     \
                                                                              \
        /*vector_capacity*/                                                   \
        size_t _PREFIX##_vector_capacity(struct _PREFIX##_Vector* vector) {   \
                return vector->capacity;                                      \
        }                                                                     \
                                                                              \
        /*vector_pushback*/                                                   \
        void _PREFIX##_vector_pushback(struct _PREFIX##_Vector* vector,       \
                                       _TYPE val) {                           \
                if (_PREFIX##_vector_size(vector) ==                          \
                    _PREFIX##_vector_capacity(vector)) {                      \
                        _PREFIX##_vector_reserve(                             \
                            vector, _PREFIX##_vector_capacity(vector) * 1.5); \
                }                                                             \
                _PREFIX##_vector_set(vector, _PREFIX##_vector_size(vector),   \
                                     val);                                    \
                ++vector->size;                                               \
        }                                                                     \
                                                                              \
        /*vector_set*/                                                        \
        void _PREFIX##_vector_set(struct _PREFIX##_Vector* vector,            \
                                  size_t index, _TYPE val) {                  \
                vector->data[index] = val;                                    \
        }                                                                     \
                                                                              \
        /*vector_get*/                                                        \
        _TYPE _PREFIX##_vector_get(struct _PREFIX##_Vector* vector,           \
                                   size_t index) {                            \
                return vector->data[index];                                   \
        }                                                                     \
                                                                              \
        /*vector_remove*/                                                     \
        void _PREFIX##_vector_remove(struct _PREFIX##_Vector* vector,         \
                                     size_t index) {                          \
                for (size_t i = index; i < _PREFIX##_vector_size(vector) - 1; \
                     ++i) {                                                   \
                        _PREFIX##_vector_set(                                 \
                            vector, i, _PREFIX##_vector_get(vector, i + 1));  \
                }                                                             \
                --vector->size;                                               \
        }                                                                     \
                                                                              \
        /*vector_remove*/                                                     \
        void _PREFIX##_vector_free(struct _PREFIX##_Vector* vector) {         \
                free(vector->data);                                           \
        }
