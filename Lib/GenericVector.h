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
                                      const size_t new_capacity);              \
                                                                               \
        /* vector_resize */                                                    \
        /* resizes the size and capacity of a vector to the given size, and    \
         * fills it with a default val "val"*/                                 \
        void _PREFIX##_vector_resize(struct _PREFIX##_Vector* vector,          \
                                     const size_t new_size, const _TYPE val);  \
                                                                               \
        /* vector_size */                                                      \
        /* gets the current size of the vector (number of elements actually    \
         * being used)*/                                                       \
        size_t _PREFIX##_vector_size(const struct _PREFIX##_Vector* vector);   \
                                                                               \
        /* vector_capacity */                                                  \
        /* gets the current capacity of the vector */                          \
        size_t _PREFIX##_vector_capacity(                                      \
            const struct _PREFIX##_Vector* vector);                            \
                                                                               \
        /* vector_pushback */                                                  \
        /*appends something (val) to the end of the size of the vector and     \
         * increases the vector's size by one. If vectoris too small, it       \
         * reallocates the vector so that it is 1.5x the original size  */     \
        void _PREFIX##_vector_push_back(struct _PREFIX##_Vector* vector,       \
                                        const _TYPE val);                      \
                                                                               \
        /* vector_pop_back */                                                  \
        /* deletes the last element of the bector and returns the deleted      \
         * elment. Also reduces the size by 1. WARNING: does not do bounds     \
         * checking and will do strange things with empty vectors  */          \
        _TYPE _PREFIX##_vector_pop_back(struct _PREFIX##_Vector*);             \
                                                                               \
        /* vector_set */                                                       \
        /*sets a specified index to a new value (val). WARNING: does not do    \
         * bounds checking */                                                  \
        void _PREFIX##_vector_set(struct _PREFIX##_Vector*,                    \
                                  const size_t index, const _TYPE val);        \
                                                                               \
        /* vector_get */                                                       \
        /*gets the specified index of an element. WARNING does not do bounds   \
         * checking   */                                                       \
        _TYPE _PREFIX##_vector_get(const struct _PREFIX##_Vector*,             \
                                   const size_t index);                        \
        /* vector_get_p*/                                                      \
        /*gets the pointer to a specified index of an element. WARNING does    \
         * not do bounds checking   */                                         \
        _TYPE* _PREFIX##_vector_get_p(const struct _PREFIX##_Vector*,          \
                                      const size_t index);                     \
                                                                               \
        /* vector_swap */                                                      \
        /* Swaps 2 specified indexes with each other.WARNING: Does not do      \
         * bounds checking */                                                  \
        void _PREFIX##_vector_swap(struct _PREFIX##_Vector*,                   \
                                   const size_t index0, const size_t index1);  \
                                                                               \
        /* vector_swap_back */                                                 \
        /* Swaps the specified index with the last size index. WARNING: Does   \
         * not do bounds checking */                                           \
        void _PREFIX##_vector_swap_back(struct _PREFIX##_Vector*,              \
                                        const size_t index);                   \
                                                                               \
        /* vector_remove */                                                    \
        /*removes an element from the vector at and index and shifts all       \
         * elements to the right of it back 1. Reduces the size of the vector  \
         * by one as well. WARNING does not do bounds checking   */            \
        void _PREFIX##_vector_remove(struct _PREFIX##_Vector*,                 \
                                     const size_t index);                      \
                                                                               \
        /* vector_free */                                                      \
        /*frees the memory allocated by the vector.       */                   \
        void _PREFIX##_vector_free(struct _PREFIX##_Vector*);

#define VECTOR_DEFINE(_TYPE, _PREFIX)                                          \
        /*vector_init*/                                                        \
        void _PREFIX##_vector_init(struct _PREFIX##_Vector* vector) {          \
                vector->size = 0;                                              \
                vector->capacity = 0;                                          \
                vector->data = (_TYPE*)safe_malloc(0);                         \
        }                                                                      \
                                                                               \
        /*vector_reserve*/                                                     \
        void _PREFIX##_vector_reserve(struct _PREFIX##_Vector* vector,         \
                                      const size_t new_capacity) {             \
                _TYPE* new_data = (_TYPE*)realloc(                             \
                    vector->data, sizeof(_TYPE) * new_capacity);               \
                if (new_data == NULL) {                                        \
                        fprintf(stderr,                                        \
                                "Error: insufficient memory upon vector "      \
                                "allocation");                                 \
                        exit(0);                                               \
                } else {                                                       \
                        vector->data = new_data;                               \
                        new_data = NULL;                                       \
                        vector->capacity = new_capacity;                       \
                }                                                              \
        }                                                                      \
                                                                               \
        /*vector_resize*/                                                      \
        void _PREFIX##_vector_resize(struct _PREFIX##_Vector* vector,          \
                                     const size_t new_size, const _TYPE val) { \
                _PREFIX##_vector_reserve(vector, new_size);                    \
                for (size_t i = vector->size; i < vector->capacity; ++i) {     \
                        _PREFIX##_vector_set(vector, i, val);                  \
                }                                                              \
                vector->size = new_size;                                       \
                vector->capacity = new_size;                                   \
        }                                                                      \
                                                                               \
        /*vector_size*/                                                        \
        size_t _PREFIX##_vector_size(const struct _PREFIX##_Vector* vector) {  \
                return vector->size;                                           \
        }                                                                      \
                                                                               \
        /*vector_capacity*/                                                    \
        size_t _PREFIX##_vector_capacity(                                      \
            const struct _PREFIX##_Vector* vector) {                           \
                return vector->capacity;                                       \
        }                                                                      \
                                                                               \
        /*vector_pushback*/                                                    \
        void _PREFIX##_vector_push_back(struct _PREFIX##_Vector* vector,       \
                                        const _TYPE val) {                     \
                if (_PREFIX##_vector_size(vector) ==                           \
                    _PREFIX##_vector_capacity(vector)) {                       \
                        _PREFIX##_vector_reserve(                              \
                            vector, _PREFIX##_vector_capacity(vector) * 1.5);  \
                }                                                              \
                _PREFIX##_vector_set(vector, _PREFIX##_vector_size(vector),    \
                                     val);                                     \
                ++vector->size;                                                \
        }                                                                      \
                                                                               \
        /* vector_pop_back */                                                  \
        _TYPE _PREFIX##_vector_pop_back(struct _PREFIX##_Vector* vector) {     \
                _TYPE element = _PREFIX##_vector_get(                          \
                    vector, _PREFIX##_vector_size(vector) - 1);                \
                _PREFIX##_vector_remove(vector,                                \
                                        _PREFIX##_vector_size(vector));        \
                return element;                                                \
        }                                                                      \
                                                                               \
        /*vector_set*/                                                         \
        void _PREFIX##_vector_set(struct _PREFIX##_Vector* vector,             \
                                  const size_t index, const _TYPE val) {       \
                vector->data[index] = val;                                     \
        }                                                                      \
                                                                               \
        /*vector_get*/                                                         \
        _TYPE _PREFIX##_vector_get(const struct _PREFIX##_Vector* vector,      \
                                   const size_t index) {                       \
                return vector->data[index];                                    \
        }                                                                      \
                                                                               \
        /*vector_get_p*/                                                       \
        _TYPE* _PREFIX##_vector_get_p(const struct _PREFIX##_Vector* vector,   \
                                      const size_t index) {                    \
                return vector->data + index;                                   \
        }                                                                      \
                                                                               \
        /* vector_swap */                                                      \
        void _PREFIX##_vector_swap(struct _PREFIX##_Vector* vector,            \
                                   const size_t index0, const size_t index1) { \
                _TYPE tmp = _PREFIX##_vector_get(vector, index0);              \
                _PREFIX##_vector_set(vector, index0,                           \
                                     _PREFIX##_vector_get(vector, index1));    \
                _PREFIX##_vector_set(vector, index1, tmp);                     \
        }                                                                      \
                                                                               \
        /* vector_swap_back */                                                 \
        void _PREFIX##_vector_swap_back(struct _PREFIX##_Vector* vector,       \
                                        const size_t index) {                  \
                _PREFIX##_vector_swap(vector, index,                           \
                                      _PREFIX##_vector_size(vector) - 1);      \
        }                                                                      \
                                                                               \
        /*vector_remove*/                                                      \
        void _PREFIX##_vector_remove(struct _PREFIX##_Vector* vector,          \
                                     const size_t index) {                     \
                for (size_t i = index; i < _PREFIX##_vector_size(vector) - 1;  \
                     ++i) {                                                    \
                        _PREFIX##_vector_set(                                  \
                            vector, i, _PREFIX##_vector_get(vector, i + 1));   \
                }                                                              \
                --vector->size;                                                \
        }                                                                      \
                                                                               \
        /*vector_free*/                                                        \
        void _PREFIX##_vector_free(struct _PREFIX##_Vector* vector) {          \
                free(vector->data);                                            \
        }
