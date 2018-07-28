#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "Util.h"

/**
 * Macros for a vector (a wrapper for a continious memory object). Not C++
 * standard compliant.
 */

#define VECTOR_DECLARE(TYPE, PREFIX) VECTOR_TYPE_DECLARE(TYPE, PREFIX##Vector)
#define VECTOR_DEFINE(TYPE, PREFIX) VECTOR_TYPE_DEFINE(TYPE, PREFIX##Vector)

#define VECTOR_TYPE_DECLARE(TYPE, NAME)                                        \
	/* Types... */                                                         \
	/* --------------------- */                                            \
                                                                               \
	struct NAME;                                                           \
	struct NAME {                                                          \
		size_t size;     /* sizeof the current elements in use */      \
		size_t capacity; /*total memory available for x elements */    \
		TYPE *data;      /* actual data*/                              \
	};                                                                     \
                                                                               \
	/* Procedures... */                                                    \
	/* --------------------- */                                            \
                                                                               \
	/* vector_init */                                                      \
	/* initializes a vector */                                             \
	void NAME##_init(struct NAME *vector);                                 \
                                                                               \
	/* vector_reserve */                                                   \
	/* increases (or decreases) the capacity of a vector to the given size \
	 */                                                                    \
	void NAME##_reserve(struct NAME *vector, const size_t new_capacity);   \
                                                                               \
	/* vector_resize */                                                    \
	/* resizes the size and capacity of a vector to the given size, and    \
	 * fills it with a default val "val"*/                                 \
	void NAME##_resize(struct NAME *vector, const size_t new_size,         \
			   const TYPE val);                                    \
                                                                               \
	/* vector_size */                                                      \
	/* gets the current size of the vector (number of elements actually    \
	 * being used)*/                                                       \
	size_t NAME##_size(const struct NAME *vector);                         \
                                                                               \
	/* vector_capacity */                                                  \
	/* gets the current capacity of the vector */                          \
	size_t NAME##_capacity(const struct NAME *vector);                     \
                                                                               \
	/* vector_pushback */                                                  \
	/*appends something (val) to the end of the size of the vector and     \
	 * increases the vector's size by one. If vectoris too small, it       \
	 * reallocates the vector so that it is 1.5x the original size  */     \
	void NAME##_push_back(struct NAME *vector, const TYPE val);            \
                                                                               \
	/* vector_pop_back */                                                  \
	/* deletes the last element of the bector and returns the deleted      \
	 * elment. Also reduces the size by 1. WARNING: does not do bounds     \
	 * checking and will do strange things with empty vectors  */          \
	TYPE NAME##_pop_back(struct NAME *);                                   \
                                                                               \
	/* vector_set */                                                       \
	/*sets a specified index to a new value (val). WARNING: does not do    \
	 * bounds checking */                                                  \
	void NAME##_set(struct NAME *, const size_t index, const TYPE val);    \
                                                                               \
	/* vector_get */                                                       \
	/*gets the specified index of an element. WARNING does not do bounds   \
	 * checking   */                                                       \
	TYPE NAME##_get(const struct NAME *, const size_t index);              \
	/* vector_get_p*/                                                      \
	/*gets the pointer to a specified index of an element. WARNING does    \
	 * not do bounds checking   */                                         \
	TYPE *NAME##_get_p(const struct NAME *const, const size_t index);      \
                                                                               \
	/* vector_swap */                                                      \
	/* Swaps 2 specified indexes with each other.WARNING: Does not do      \
	 * bounds checking */                                                  \
	void NAME##_swap(struct NAME *, const size_t index0,                   \
			 const size_t index1);                                 \
                                                                               \
	/* vector_swap_back */                                                 \
	/* Swaps the specified index with the last size index. WARNING: Does   \
	 * not do bounds checking */                                           \
	void NAME##_swap_back(struct NAME *, const size_t index);              \
                                                                               \
	/* vector_remove */                                                    \
	/*removes an element from the vector at and index and shifts all       \
	 * elements to the right of it back 1. Reduces the size of the vector  \
	 * by one as well. WARNING does not do bounds checking   */            \
	void NAME##_remove(struct NAME *, const size_t index);                 \
                                                                               \
	/* vector_lazy_clear */                                                \
	/*lazily clears a vector by setting the size back to 0*/               \
	void NAME##_lazy_clear(struct NAME *);                                 \
                                                                               \
	/* vector_free */                                                      \
	/*frees the memory allocated by the vector.       */                   \
	void NAME##_free(struct NAME *);

#define VECTOR_TYPE_DEFINE(TYPE, NAME)                                                                                             \
	/*vector_init*/                                                                                                            \
	void NAME##_init(struct NAME *vector)                                                                                      \
	{                                                                                                                          \
		vector->size = 0;                                                                                                  \
		vector->capacity = 0;                                                                                              \
		vector->data = (TYPE *)safe_malloc(0);                                                                             \
	}                                                                                                                          \
                                                                                                                                   \
	/*vector_reserve*/                                                                                                         \
	void NAME##_reserve(struct NAME *vector, const size_t new_capacity)                                                        \
	{                                                                                                                          \
		TYPE *new_data = (TYPE *)realloc(vector->data,                                                                     \
						 sizeof(TYPE) * new_capacity);                                                     \
                                                                                                                                   \
		if (new_data == NULL) {                                                                                            \
			fprintf(stderr,                                                                                            \
				"Error: insufficient memory with vector (TYPE: " #TYPE                                             \
				", " #NAME " in allocation from the " #NAME                                                        \
				"_reserve function.\n Current size: %lu. Current capcity: %lu. \n Requested new capacity: %lu \n", \
				NAME##_size(vector), NAME##_capacity(vector),                                                      \
				new_capacity);                                                                                     \
			printf("This occured at file: "__FILE__);                                                                  \
			exit(0);                                                                                                   \
		} else {                                                                                                           \
			vector->data = new_data;                                                                                   \
			new_data = NULL;                                                                                           \
			vector->capacity = new_capacity;                                                                           \
		}                                                                                                                  \
	}                                                                                                                          \
                                                                                                                                   \
	/*vector_resize*/                                                                                                          \
	void NAME##_resize(struct NAME *vector, const size_t new_size,                                                             \
			   const TYPE val)                                                                                         \
	{                                                                                                                          \
		NAME##_reserve(vector, new_size);                                                                                  \
		for (size_t i = vector->size; i < vector->capacity; ++i) {                                                         \
			NAME##_set(vector, i, val);                                                                                \
		}                                                                                                                  \
		vector->size = new_size;                                                                                           \
		vector->capacity = new_size;                                                                                       \
	}                                                                                                                          \
                                                                                                                                   \
	/*vector_size*/                                                                                                            \
	size_t NAME##_size(const struct NAME *vector)                                                                              \
	{                                                                                                                          \
		return vector->size;                                                                                               \
	}                                                                                                                          \
                                                                                                                                   \
	/*vector_capacity*/                                                                                                        \
	size_t NAME##_capacity(const struct NAME *vector)                                                                          \
	{                                                                                                                          \
		return vector->capacity;                                                                                           \
	}                                                                                                                          \
                                                                                                                                   \
	/*vector_pushback*/                                                                                                        \
	void NAME##_push_back(struct NAME *vector, const TYPE val)                                                                 \
	{                                                                                                                          \
		if (NAME##_size(vector) == NAME##_capacity(vector)) {                                                              \
			NAME##_reserve(vector, NAME##_capacity(vector) * 1.5);                                                     \
		}                                                                                                                  \
		NAME##_set(vector, NAME##_size(vector), val);                                                                      \
		++vector->size;                                                                                                    \
	}                                                                                                                          \
                                                                                                                                   \
	/* vector_pop_back */                                                                                                      \
	TYPE NAME##_pop_back(struct NAME *vector)                                                                                  \
	{                                                                                                                          \
		TYPE element = NAME##_get(vector, NAME##_size(vector) - 1);                                                        \
		--vector->size;                                                                                                    \
		return element;                                                                                                    \
	}                                                                                                                          \
                                                                                                                                   \
	/*vector_set*/                                                                                                             \
	void NAME##_set(struct NAME *vector, const size_t index,                                                                   \
			const TYPE val)                                                                                            \
	{                                                                                                                          \
		vector->data[index] = val;                                                                                         \
	}                                                                                                                          \
                                                                                                                                   \
	/*vector_get*/                                                                                                             \
	TYPE NAME##_get(const struct NAME *vector, const size_t index)                                                             \
	{                                                                                                                          \
		return vector->data[index];                                                                                        \
	}                                                                                                                          \
                                                                                                                                   \
	/*vector_get_p*/                                                                                                           \
	TYPE *NAME##_get_p(const struct NAME *const vector,                                                                        \
			   const size_t index)                                                                                     \
	{                                                                                                                          \
		return vector->data + index;                                                                                       \
	}                                                                                                                          \
                                                                                                                                   \
	/* vector_swap */                                                                                                          \
	void NAME##_swap(struct NAME *vector, const size_t index0,                                                                 \
			 const size_t index1)                                                                                      \
	{                                                                                                                          \
		TYPE tmp = NAME##_get(vector, index0);                                                                             \
		NAME##_set(vector, index0, NAME##_get(vector, index1));                                                            \
		NAME##_set(vector, index1, tmp);                                                                                   \
	}                                                                                                                          \
                                                                                                                                   \
	/* vector_swap_back */                                                                                                     \
	void NAME##_swap_back(struct NAME *vector, const size_t index)                                                             \
	{                                                                                                                          \
		NAME##_swap(vector, index, NAME##_size(vector) - 1);                                                               \
	}                                                                                                                          \
                                                                                                                                   \
	/*vector_remove*/                                                                                                          \
	void NAME##_remove(struct NAME *vector, const size_t index)                                                                \
	{                                                                                                                          \
		for (size_t i = index; i < NAME##_size(vector) - 1; ++i) {                                                         \
			NAME##_set(vector, i, NAME##_get(vector, i + 1));                                                          \
		}                                                                                                                  \
		--vector->size;                                                                                                    \
	}                                                                                                                          \
                                                                                                                                   \
	/* vector_lazy_clear */                                                                                                    \
	void NAME##_lazy_clear(struct NAME *vector)                                                                                \
	{                                                                                                                          \
		vector->size = 0;                                                                                                  \
	}                                                                                                                          \
                                                                                                                                   \
	/*vector_free*/                                                                                                            \
	void NAME##_free(struct NAME *vector)                                                                                      \
	{                                                                                                                          \
		free(vector->data);                                                                                                \
	}
