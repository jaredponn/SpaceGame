#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "Util.h"

/**
 * Macros for a vector (a wrapper for a continious memory object). Not C++
 * standard compliant.
 */

#define VECTOR_DECLARE(TYPE, PREFIX)                                           \
        /* Types... */                                                         \
        /* --------------------- */                                            \
                                                                               \
        struct PREFIX##_Vector;                                                \
        struct PREFIX##_Vector {                                               \
                size_t size;     /* sizeof the current elements in use */      \
                size_t capacity; /*total memory available for x elements */    \
                TYPE* data;      /* actual data*/                              \
        };                                                                     \
                                                                               \
        /* Procedures... */                                                    \
        /* --------------------- */                                            \
                                                                               \
        /* vector_init */                                                      \
        /* initializes a vector */                                             \
        void PREFIX##_vector_init(struct PREFIX##_Vector* vector);             \
                                                                               \
        /* vector_reserve */                                                   \
        /* increases (or decreases) the capacity of a vector to the given size \
         */                                                                    \
        void PREFIX##_vector_reserve(struct PREFIX##_Vector* vector,           \
                                     const size_t new_capacity);               \
                                                                               \
        /* vector_resize */                                                    \
        /* resizes the size and capacity of a vector to the given size, and    \
         * fills it with a default val "val"*/                                 \
        void PREFIX##_vector_resize(struct PREFIX##_Vector* vector,            \
                                    const size_t new_size, const TYPE val);    \
                                                                               \
        /* vector_size */                                                      \
        /* gets the current size of the vector (number of elements actually    \
         * being used)*/                                                       \
        size_t PREFIX##_vector_size(const struct PREFIX##_Vector* vector);     \
                                                                               \
        /* vector_capacity */                                                  \
        /* gets the current capacity of the vector */                          \
        size_t PREFIX##_vector_capacity(const struct PREFIX##_Vector* vector); \
                                                                               \
        /* vector_pushback */                                                  \
        /*appends something (val) to the end of the size of the vector and     \
         * increases the vector's size by one. If vectoris too small, it       \
         * reallocates the vector so that it is 1.5x the original size  */     \
        void PREFIX##_vector_push_back(struct PREFIX##_Vector* vector,         \
                                       const TYPE val);                        \
                                                                               \
        /* vector_pop_back */                                                  \
        /* deletes the last element of the bector and returns the deleted      \
         * elment. Also reduces the size by 1. WARNING: does not do bounds     \
         * checking and will do strange things with empty vectors  */          \
        TYPE PREFIX##_vector_pop_back(struct PREFIX##_Vector*);                \
                                                                               \
        /* vector_set */                                                       \
        /*sets a specified index to a new value (val). WARNING: does not do    \
         * bounds checking */                                                  \
        void PREFIX##_vector_set(struct PREFIX##_Vector*, const size_t index,  \
                                 const TYPE val);                              \
                                                                               \
        /* vector_get */                                                       \
        /*gets the specified index of an element. WARNING does not do bounds   \
         * checking   */                                                       \
        TYPE PREFIX##_vector_get(const struct PREFIX##_Vector*,                \
                                 const size_t index);                          \
        /* vector_get_p*/                                                      \
        /*gets the pointer to a specified index of an element. WARNING does    \
         * not do bounds checking   */                                         \
        TYPE* PREFIX##_vector_get_p(const struct PREFIX##_Vector* const,       \
                                    const size_t index);                       \
                                                                               \
        /* vector_swap */                                                      \
        /* Swaps 2 specified indexes with each other.WARNING: Does not do      \
         * bounds checking */                                                  \
        void PREFIX##_vector_swap(struct PREFIX##_Vector*,                     \
                                  const size_t index0, const size_t index1);   \
                                                                               \
        /* vector_swap_back */                                                 \
        /* Swaps the specified index with the last size index. WARNING: Does   \
         * not do bounds checking */                                           \
        void PREFIX##_vector_swap_back(struct PREFIX##_Vector*,                \
                                       const size_t index);                    \
                                                                               \
        /* vector_remove */                                                    \
        /*removes an element from the vector at and index and shifts all       \
         * elements to the right of it back 1. Reduces the size of the vector  \
         * by one as well. WARNING does not do bounds checking   */            \
        void PREFIX##_vector_remove(struct PREFIX##_Vector*,                   \
                                    const size_t index);                       \
                                                                               \
        /* vector_lazy_clear */                                                \
        /*lazily clears a vector by setting the size back to 0*/               \
        void PREFIX##_vector_lazy_clear(struct PREFIX##_Vector*);              \
                                                                               \
        /* vector_free */                                                      \
        /*frees the memory allocated by the vector.       */                   \
        void PREFIX##_vector_free(struct PREFIX##_Vector*);

#define VECTOR_DEFINE(TYPE, PREFIX)                                            \
        /*vector_init*/                                                        \
        void PREFIX##_vector_init(struct PREFIX##_Vector* vector) {            \
                vector->size = 0;                                              \
                vector->capacity = 0;                                          \
                vector->data = (TYPE*)safe_malloc(0);                          \
        }                                                                      \
                                                                               \
        /*vector_reserve*/                                                     \
        void PREFIX##_vector_reserve(struct PREFIX##_Vector* vector,           \
                                     const size_t new_capacity) {              \
                TYPE* new_data =                                               \
                    (TYPE*)realloc(vector->data, sizeof(TYPE) * new_capacity); \
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
        void PREFIX##_vector_resize(struct PREFIX##_Vector* vector,            \
                                    const size_t new_size, const TYPE val) {   \
                PREFIX##_vector_reserve(vector, new_size);                     \
                for (size_t i = vector->size; i < vector->capacity; ++i) {     \
                        PREFIX##_vector_set(vector, i, val);                   \
                }                                                              \
                vector->size = new_size;                                       \
                vector->capacity = new_size;                                   \
        }                                                                      \
                                                                               \
        /*vector_size*/                                                        \
        size_t PREFIX##_vector_size(const struct PREFIX##_Vector* vector) {    \
                return vector->size;                                           \
        }                                                                      \
                                                                               \
        /*vector_capacity*/                                                    \
        size_t PREFIX##_vector_capacity(                                       \
            const struct PREFIX##_Vector* vector) {                            \
                return vector->capacity;                                       \
        }                                                                      \
                                                                               \
        /*vector_pushback*/                                                    \
        void PREFIX##_vector_push_back(struct PREFIX##_Vector* vector,         \
                                       const TYPE val) {                       \
                if (PREFIX##_vector_size(vector) ==                            \
                    PREFIX##_vector_capacity(vector)) {                        \
                        PREFIX##_vector_reserve(                               \
                            vector, PREFIX##_vector_capacity(vector) * 1.5);   \
                }                                                              \
                PREFIX##_vector_set(vector, PREFIX##_vector_size(vector),      \
                                    val);                                      \
                ++vector->size;                                                \
        }                                                                      \
                                                                               \
        /* vector_pop_back */                                                  \
        TYPE PREFIX##_vector_pop_back(struct PREFIX##_Vector* vector) {        \
                TYPE element = PREFIX##_vector_get(                            \
                    vector, PREFIX##_vector_size(vector) - 1);                 \
                PREFIX##_vector_remove(vector, PREFIX##_vector_size(vector));  \
                return element;                                                \
        }                                                                      \
                                                                               \
        /*vector_set*/                                                         \
        void PREFIX##_vector_set(struct PREFIX##_Vector* vector,               \
                                 const size_t index, const TYPE val) {         \
                vector->data[index] = val;                                     \
        }                                                                      \
                                                                               \
        /*vector_get*/                                                         \
        TYPE PREFIX##_vector_get(const struct PREFIX##_Vector* vector,         \
                                 const size_t index) {                         \
                return vector->data[index];                                    \
        }                                                                      \
                                                                               \
        /*vector_get_p*/                                                       \
        TYPE* PREFIX##_vector_get_p(                                           \
            const struct PREFIX##_Vector* const vector, const size_t index) {  \
                return vector->data + index;                                   \
        }                                                                      \
                                                                               \
        /* vector_swap */                                                      \
        void PREFIX##_vector_swap(struct PREFIX##_Vector* vector,              \
                                  const size_t index0, const size_t index1) {  \
                TYPE tmp = PREFIX##_vector_get(vector, index0);                \
                PREFIX##_vector_set(vector, index0,                            \
                                    PREFIX##_vector_get(vector, index1));      \
                PREFIX##_vector_set(vector, index1, tmp);                      \
        }                                                                      \
                                                                               \
        /* vector_swap_back */                                                 \
        void PREFIX##_vector_swap_back(struct PREFIX##_Vector* vector,         \
                                       const size_t index) {                   \
                PREFIX##_vector_swap(vector, index,                            \
                                     PREFIX##_vector_size(vector) - 1);        \
        }                                                                      \
                                                                               \
        /*vector_remove*/                                                      \
        void PREFIX##_vector_remove(struct PREFIX##_Vector* vector,            \
                                    const size_t index) {                      \
                for (size_t i = index; i < PREFIX##_vector_size(vector) - 1;   \
                     ++i) {                                                    \
                        PREFIX##_vector_set(                                   \
                            vector, i, PREFIX##_vector_get(vector, i + 1));    \
                }                                                              \
                --vector->size;                                                \
        }                                                                      \
                                                                               \
        /* vector_lazy_clear */                                                \
        void PREFIX##_vector_lazy_clear(struct PREFIX##_Vector* vector) {      \
                vector->size = 0;                                              \
        }                                                                      \
                                                                               \
        /*vector_free*/                                                        \
        void PREFIX##_vector_free(struct PREFIX##_Vector* vector) {            \
                free(vector->data);                                            \
        }
