#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "mlib.h"
#include "minternals.h"

#ifndef MLIB_INCLUDED
#error Include the ``mlib.h'' file before including an other mlib file
#endif
/**
 * Macros for a vector (a wrapper for a continious memory object). Not C++
 * standard compliant.
 */

// -----------------------------------------
//    Function interface
// -----------------------------------------
// TYPE must be not be a pointer. A typedeffed pointer is a workaround of this
#define MVECTOR_DECLARE(TYPE) VECTOR_TYPE_DECLARE(TYPE)

// -----------------------------------------
//    Functions
// -----------------------------------------
#define MVECTOR_INIT(TYPE) MK_FUNC(MK_VEC(TYPE), init)
#define MVECTOR_RESERVE(TYPE) MK_FUNC(MK_VEC(TYPE), reserve)
#define MVECTOR_RESIZE(TYPE) MK_FUNC(MK_VEC(TYPE), resize)
#define MVECTOR_SIZE(TYPE) MK_FUNC(MK_VEC(TYPE), size)
#define MVECTOR_CAPACITY(TYPE) MK_FUNC(MK_VEC(TYPE), capacity)

/* vector_pushback */
/*appends something (val) to the end of the size of the vector and
 * increases the vector's size by one. If vectoris too small, it
 * reallocates the vector so that it is 1.5x the original size  */
#define MVECTOR_PUSH_BACK(TYPE) MK_FUNC(MK_VEC(TYPE), push_back)

/* vector_pop_back */
/* deletes the last element of the bector and returns the deleted
 * elment. Also reduces the size by 1. WARNING: does not do bounds
 * checking and will do strange things with empty vectors  */
#define MVECTOR_POP_BACK(TYPE) MK_FUNC(MK_VEC(TYPE), pop_back)

/* vector_set */
/*sets a specified index to a new value (val). WARNING: does not do
 * bounds checking */
#define MVECTOR_SET(TYPE) MK_FUNC(MK_VEC(TYPE), set)
#define MVECTOR_SET_AT(TYPE) MK_FUNC(MK_VEC(TYPE), set)

#define MVECTOR_GET_AT(TYPE) MK_FUNC(MK_VEC(TYPE), get)
#define MVECTOR_GET_P_AT(TYPE) MK_FUNC(MK_VEC(TYPE), get_p)
#define MVECTOR_GET(TYPE) MK_FUNC(MK_VEC(TYPE), get)
#define MVECTOR_GET_P(TYPE) MK_FUNC(MK_VEC(TYPE), get_p)

/* vector_swap */
/* Swaps 2 specified indexes with each other.WARNING: Does not do
 * bounds checking */
#define MVECTOR_SWAP(TYPE) MK_FUNC(MK_VEC(TYPE), swap)

/* vector_swap_back */
/* Swaps the specified index with the last size index. WARNING: Does
 * not do bounds checking */
#define MVECTOR_SWAP_BACK(TYPE) MK_FUNC(MK_VEC(TYPE), swap_back)

#define MVECTOR_REMOVE(TYPE) MK_FUNC(MK_VEC(TYPE), remove)
#define MVECTOR_LAZY_CLEAR(TYPE) MK_FUNC(MK_VEC(TYPE), lazy_clear)

/*vector_fill*/
/*fills the entire capacity of the vector with the given value*/
#define MVECTOR_FILL(TYPE) MK_FUNC(MK_VEC(TYPE), fill)

/*TODO*/
#define MVECTOR_RESERVE(TYPE) MK_FUNC(MK_VEC(TYPE), reserve)
#define MVECTOR_FREE(TYPE) MK_FUNC(MK_VEC(TYPE), free)


// -----------------------------------------
//    Debug macros
// -----------------------------------------

/* if MLIB_DEBUG is enabled, then include the debug macros */
#ifdef MLIB_DEBUG
// asserts that the inital capacity of a vector must be greater than 0
#define DBG_VECTOR_INIT_CAPACITY_ASSERTION(capacity)                                      \
	if (capacity <= 0) {                                                              \
		printf("MLIB VECTOR_INIT ERROR AT FILE: " GET_FILE_NAME()               \
		       ". Initial capacity must be greater than 0.\nAborting... \n"); \
		abort();                                                                  \
	}

/* otherwise do not include the extra dubggin checks */
#else
#define DBG_VECTOR_INIT_CAPACITY_ASSERTION(capacity)
#endif

// -----------------------------------------
//    Macro to generate c code
// -----------------------------------------

// names the vector
#define MK_VEC(NAME) MVector_##NAME##_t


// creates the vector
#define VECTOR_TYPE_DECLARE(TYPE)                                                              \
	/* Types... */                                                                         \
	/* --------------------- */                                                            \
                                                                                               \
	typedef struct MK_VEC(TYPE) {                                                          \
		msize size;     /* sizeof the current elements in use */                       \
		msize capacity; /*total memory available for x elements */                     \
		TYPE *data;     /* actual data*/                                               \
	} MK_VEC(TYPE);                                                                        \
                                                                                               \
	/* Declarations... */                                                                  \
	/* --------------------- */                                                            \
	static inline void MK_FUNC(MK_VEC(TYPE), init)(                                        \
		struct MK_VEC(TYPE) * vector, msize capacity);                                 \
	static inline void MK_FUNC(MK_VEC(TYPE), reserve)(                                     \
		struct MK_VEC(TYPE) * vector, const msize new_capacity);                       \
	static inline void MK_FUNC(MK_VEC(TYPE), resize)(                                      \
		struct MK_VEC(TYPE) * vector, const msize new_size,                            \
		const TYPE val);                                                               \
	static inline msize MK_FUNC(MK_VEC(TYPE),                                              \
				    size)(const struct MK_VEC(TYPE) * vector);                 \
	static inline msize MK_FUNC(MK_VEC(TYPE), capacity)(                                   \
		const struct MK_VEC(TYPE) * vector);                                           \
	static inline void MK_FUNC(MK_VEC(TYPE), push_back)(                                   \
		struct MK_VEC(TYPE) * vector, const TYPE val);                                 \
	static inline TYPE MK_FUNC(MK_VEC(TYPE),                                               \
				   pop_back)(struct MK_VEC(TYPE) * vector);                    \
	static inline void MK_FUNC(MK_VEC(TYPE),                                               \
				   set)(struct MK_VEC(TYPE) * vector,                          \
					const msize index, const TYPE val);                    \
	static inline TYPE MK_FUNC(MK_VEC(TYPE), get)(                                         \
		const struct MK_VEC(TYPE) * vector, const msize index);                        \
	static inline TYPE *MK_FUNC(MK_VEC(TYPE), get_p)(                                      \
		const struct MK_VEC(TYPE) *const vector, const msize index);                   \
	static inline void MK_FUNC(MK_VEC(TYPE), swap)(                                        \
		struct MK_VEC(TYPE) * vector, const msize index0,                              \
		const msize index1);                                                           \
	static inline void MK_FUNC(MK_VEC(TYPE), swap_back)(                                   \
		struct MK_VEC(TYPE) * vector, const msize index);                              \
	static inline void MK_FUNC(MK_VEC(TYPE), remove)(                                      \
		struct MK_VEC(TYPE) * vector, const msize index);                              \
	static inline void MK_FUNC(MK_VEC(TYPE),                                               \
				   lazy_clear)(struct MK_VEC(TYPE) * vector);                  \
	static inline void MK_FUNC(MK_VEC(TYPE), fill)(                                        \
		struct MK_VEC(TYPE) * vector, const TYPE val);                                 \
	static inline void MK_FUNC(MK_VEC(TYPE),                                               \
				   free)(struct MK_VEC(TYPE) * vector);                        \
                                                                                               \
                                                                                               \
	/* Implementations... */                                                               \
	/* --------------------- */                                                            \
                                                                                               \
	/* vector_init */                                                                      \
	/* initializes a vector */                                                             \
	static inline void MK_FUNC(MK_VEC(TYPE), init)(                                        \
		struct MK_VEC(TYPE) * vector, msize capacity)                                  \
	{                                                                                      \
		DBG_VECTOR_INIT_CAPACITY_ASSERTION(capacity);                                  \
		vector->size = 0;                                                              \
		vector->capacity = capacity;                                                   \
		vector->data = (TYPE *)malloc(capacity * sizeof(TYPE));                        \
	}                                                                                      \
                                                                                               \
	/* vector_reserve */                                                                   \
	/* increases (or decreases) the capacity of a vector to the given size                 \
	 */                                                                                    \
	static inline void MK_FUNC(MK_VEC(TYPE), reserve)(                                     \
		struct MK_VEC(TYPE) * vector, const msize new_capacity)                        \
	{                                                                                      \
		TYPE *new_data = (TYPE *)realloc(vector->data,                                 \
						 sizeof(TYPE) * new_capacity);                 \
                                                                                               \
		if (new_data == NULL) {                                                        \
			fprintf(stderr,                                                      \
				"Error: insufficient memory with vector (TYPE: " #TYPE       \
				", " EVAL(DEFER1(STR)(MK_VEC(TYPE))) " in allocation from the " \
                                        EVAL(DEFER1(STR)(MK_VEC(TYPE)))                \
				"_reserve function.\n Current size: %lu. "   \
				"Current capcity: %lu. \n Requested new capacity: %lu \n", \
				MVECTOR_SIZE(TYPE)(vector),                               \
				MVECTOR_CAPACITY(TYPE)(vector),                           \
				new_capacity); \
			fprintf(stderr, "This occured at file: "__FILE__);                     \
			exit(0);                                                               \
		} else {                                                                       \
			vector->data = new_data;                                               \
			new_data = NULL;                                                       \
			vector->capacity = new_capacity;                                       \
		}                                                                              \
	}                                                                                      \
                                                                                               \
	/* vector_resize */                                                                    \
	/* resizes the size and capacity of a vector to the given size, and                    \
	 * fills it with a default val "val"*/                                                 \
	static inline void MK_FUNC(MK_VEC(TYPE), resize)(                                      \
		struct MK_VEC(TYPE) * vector, const msize new_size,                            \
		const TYPE val)                                                                \
	{                                                                                      \
		MVECTOR_RESERVE(TYPE)(vector, new_size);                                       \
		for (msize i = vector->size; i < vector->capacity; ++i) {                      \
			MK_FUNC(MK_VEC(TYPE), set)(vector, i, val);                            \
		}                                                                              \
		vector->size = new_size;                                                       \
		vector->capacity = new_size;                                                   \
	}                                                                                      \
                                                                                               \
	/* vector_size */                                                                      \
	/* gets the current size of the vector (number of elements actually                    \
	 * being used)*/                                                                       \
	static inline msize MK_FUNC(MK_VEC(TYPE),                                              \
				    size)(const struct MK_VEC(TYPE) * vector)                  \
	{                                                                                      \
		return vector->size;                                                           \
	}                                                                                      \
                                                                                               \
	/* vector_capacity */                                                                  \
	/* gets the current capacity of the vector */                                          \
	static inline msize MK_FUNC(MK_VEC(TYPE), capacity)(                                   \
		const struct MK_VEC(TYPE) * vector)                                            \
	{                                                                                      \
		return vector->capacity;                                                       \
	}                                                                                      \
                                                                                               \
	/* vector_pushback */                                                                  \
	/*appends something (val) to the end of the size of the vector and                     \
	 * increases the vector's size by one. If vectoris too small, it                       \
	 * reallocates the vector so that it is 1.5x the original size  */                     \
	static inline void MK_FUNC(MK_VEC(TYPE), push_back)(                                   \
		struct MK_VEC(TYPE) * vector, const TYPE val)                                  \
	{                                                                                      \
		if (MVECTOR_SIZE(TYPE)(vector)                                                 \
		    == MVECTOR_CAPACITY(TYPE)(vector)) {                                       \
			MVECTOR_RESERVE(TYPE)                                                  \
			(vector, MVECTOR_CAPACITY(TYPE)(vector) * 2);                          \
		}                                                                              \
		MK_FUNC(MK_VEC(TYPE), set)                                                     \
		(vector, MK_FUNC(MK_VEC(TYPE), size)(vector), val);                            \
		++vector->size;                                                                \
	}                                                                                      \
                                                                                               \
	/* vector_pop_back */                                                                  \
	/* deletes the last element of the bector and returns the deleted                      \
	 * elment. Also reduces the size by 1. WARNING: does not do bounds                     \
	 * checking and will do strange things with empty vectors  */                          \
	static inline TYPE MK_FUNC(MK_VEC(TYPE),                                               \
				   pop_back)(struct MK_VEC(TYPE) * vector)                     \
	{                                                                                      \
		TYPE element = MK_FUNC(MK_VEC(TYPE), get)(                                     \
			vector, MK_FUNC(MK_VEC(TYPE), size)(vector) - 1);                      \
		--vector->size;                                                                \
		return element;                                                                \
	}                                                                                      \
                                                                                               \
	/* vector_set */                                                                       \
	/*sets a specified index to a new value (val). WARNING: does not do                    \
	 * bounds checking */                                                                  \
	static inline void MK_FUNC(MK_VEC(TYPE),                                               \
				   set)(struct MK_VEC(TYPE) * vector,                          \
					const msize index, const TYPE val)                     \
	{                                                                                      \
		vector->data[index] = val;                                                     \
	}                                                                                      \
                                                                                               \
	/* vector_get */                                                                       \
	/*gets the specified index of an element. WARNING does not do bounds                   \
	 * checking   */                                                                       \
	static inline TYPE MK_FUNC(MK_VEC(TYPE), get)(                                         \
		const struct MK_VEC(TYPE) * vector, const msize index)                         \
	{                                                                                      \
		return vector->data[index];                                                    \
	}                                                                                      \
                                                                                               \
	/* vector_get_p*/                                                                      \
	/*gets the pointer to a specified index of an element. WARNING does                    \
	 * not do bounds checking   */                                                         \
	static inline TYPE *MK_FUNC(MK_VEC(TYPE), get_p)(                                      \
		const struct MK_VEC(TYPE) *const vector, const msize index)                    \
	{                                                                                      \
		return vector->data + index;                                                   \
	}                                                                                      \
                                                                                               \
	/* vector_swap */                                                                      \
	/* Swaps 2 specified indexes with each other.WARNING: Does not do                      \
	 * bounds checking */                                                                  \
	static inline void MK_FUNC(MK_VEC(TYPE), swap)(                                        \
		struct MK_VEC(TYPE) * vector, const msize index0,                              \
		const msize index1)                                                            \
	{                                                                                      \
		TYPE tmp = MVECTOR_GET_AT(TYPE)(vector, index0);                               \
		MVECTOR_SET_AT(TYPE)                                                           \
		(vector, index0, MVECTOR_GET_AT(TYPE)(vector, index1));                        \
		MVECTOR_SET_AT(TYPE)(vector, index1, tmp);                                     \
	}                                                                                      \
                                                                                               \
	/* vector_swap_back */                                                                 \
	/* Swaps the specified index with the last size index. WARNING: Does                   \
	 * not do bounds checking */                                                           \
	static inline void MK_FUNC(MK_VEC(TYPE), swap_back)(                                   \
		struct MK_VEC(TYPE) * vector, const msize index)                               \
	{                                                                                      \
		MVECTOR_SWAP(TYPE)                                                             \
		(vector, index, MVECTOR_SIZE(TYPE)(vector) - 1);                               \
	}                                                                                      \
                                                                                               \
	/* vector_remove */                                                                    \
	/*removes an element from the vector at and index and shifts all                       \
	 * elements to the right of it back 1. Reduces the size of the vector                  \
	 * by one as well. WARNING does not do bounds checking   */                            \
	static inline void MK_FUNC(MK_VEC(TYPE), remove)(                                      \
		struct MK_VEC(TYPE) * vector, const msize index)                               \
	{                                                                                      \
		for (msize i = index; i < MVECTOR_SIZE(TYPE)(vector) - 1;                      \
		     ++i) {                                                                    \
			MVECTOR_SET(TYPE)                                                      \
			(vector, i, MVECTOR_GET(TYPE)(vector, i + 1));                         \
		}                                                                              \
		--vector->size;                                                                \
	}                                                                                      \
                                                                                               \
	/* vector_lazy_clear */                                                                \
	/*lazily clears a vector by setting the size back to 0*/                               \
	static inline void MK_FUNC(MK_VEC(TYPE),                                               \
				   lazy_clear)(struct MK_VEC(TYPE) * vector)                   \
	{                                                                                      \
		vector->size = 0;                                                              \
	}                                                                                      \
                                                                                               \
	static inline void MK_FUNC(MK_VEC(TYPE), fill)(                                        \
		struct MK_VEC(TYPE) * vector, const TYPE val)                                  \
	{                                                                                      \
		vector->size = vector->capacity;                                               \
		msize vecCapacity = vector->capacity;                                          \
		for (msize i = 0; i < vecCapacity; ++i) {                                      \
			MVECTOR_SET_AT(TYPE)(vector, i, val);                                  \
		}                                                                              \
	}                                                                                      \
                                                                                               \
	/* vector_free */                                                                      \
	/*frees the memory allocated by the vector.       */                                   \
	static inline void MVECTOR_FREE(TYPE)(struct MK_VEC(TYPE) * vector)                    \
	{                                                                                      \
		free(vector->data);                                                            \
	}
