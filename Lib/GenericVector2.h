#pragma once

#include <stdio.h>
#include <stdlib.h>
/**
 * Macros for a vector (a wrapper for a continious memory object). Not C++
 * standard compliant.
 */

// TYPE must be not be a pointer, or an otherweise typedeffed pointer
#define VECTOR_DECLARE(TYPE) VECTOR_TYPE_DECLARE(TYPE, Vector_##TYPE##_t)

// enables macros for debugging stuff
// #define ENABLE_VECTOR_DEBUG TRUE

#define VECTOR_TYPE_DECLARE(TYPE, NAME)                                                    \
	/* Types... */                                                                     \
	/* --------------------- */                                                        \
                                                                                           \
	struct NAME;                                                                       \
	struct NAME {                                                                      \
		size_t size;     /* sizeof the current elements in use */                  \
		size_t capacity; /*total memory available for x elements */                \
		TYPE *data;      /* actual data*/                                          \
	};                                                                                 \
                                                                                           \
	/* Declarations... */                                                              \
	/* --------------------- */                                                        \
	static inline void NAME##_init(struct NAME *vector);                               \
	static inline void NAME##_reserve(struct NAME *vector,                             \
					  const size_t new_capacity);                      \
	static inline void NAME##_resize(                                                  \
		struct NAME *vector, const size_t new_size, const TYPE val);               \
	static inline size_t NAME##_size(const struct NAME *vector);                       \
	static inline size_t NAME##_capacity(const struct NAME *vector);                   \
	static inline void NAME##_push_back(struct NAME *vector,                           \
					    const TYPE val);                               \
	static inline TYPE NAME##_pop_back(struct NAME *vector);                           \
	static inline void NAME##_set(struct NAME *vector, const size_t index,             \
				      const TYPE val);                                     \
	static inline TYPE NAME##_get(const struct NAME *vector,                           \
				      const size_t index);                                 \
	static inline TYPE *NAME##_get_p(const struct NAME *const vector,                  \
					 const size_t index);                              \
	static inline void NAME##_swap(struct NAME *vector,                                \
				       const size_t index0,                                \
				       const size_t index1);                               \
	static inline void NAME##_swap_back(struct NAME *vector,                           \
					    const size_t index);                           \
	static inline void NAME##_remove(struct NAME *vector,                              \
					 const size_t index);                              \
	static inline void NAME##_lazy_clear(struct NAME *vector);                         \
	static inline void NAME##_free(struct NAME *vector);                               \
                                                                                           \
                                                                                           \
	/* Implementations... */                                                           \
	/* --------------------- */                                                        \
                                                                                           \
	/* vector_init */                                                                  \
	/* initializes a vector */                                                         \
	static inline void NAME##_init(struct NAME *vector)                                \
	{                                                                                  \
		vector->size = 0;                                                          \
		vector->capacity = 1;                                                      \
		vector->data = (TYPE *)malloc(1 * sizeof(TYPE));                           \
	}                                                                                  \
                                                                                           \
	/* vector_reserve */                                                               \
	/* increases (or decreases) the capacity of a vector to the given size             \
	 */                                                                                \
	static inline void NAME##_reserve(struct NAME *vector,                             \
					  const size_t new_capacity)                       \
	{                                                                                  \
		TYPE *new_data = (TYPE *)realloc(vector->data,                             \
						 sizeof(TYPE) * new_capacity);             \
                                                                                           \
		if (new_data == NULL) {                                                    \
			fprintf(stderr,                                                    \
				"Error: insufficient memory with vector (TYPE: " #TYPE     \
				", " #NAME " in allocation from the " #NAME                \
				"_reserve function.\n Current size: %lu. "                 \
				"Current capcity: %lu. \n Requested new capacity: %lu \n", \
				NAME##_size(vector), NAME##_capacity(vector),              \
				new_capacity);                                             \
			printf("This occured at file: "__FILE__);                          \
			exit(0);                                                           \
		} else {                                                                   \
			vector->data = new_data;                                           \
			new_data = NULL;                                                   \
			vector->capacity = new_capacity;                                   \
		}                                                                          \
	}                                                                                  \
                                                                                           \
	/* vector_resize */                                                                \
	/* resizes the size and capacity of a vector to the given size, and                \
	 * fills it with a default val "val"*/                                             \
	static inline void NAME##_resize(                                                  \
		struct NAME *vector, const size_t new_size, const TYPE val)                \
	{                                                                                  \
		NAME##_reserve(vector, new_size);                                          \
		for (size_t i = vector->size; i < vector->capacity; ++i) {                 \
			NAME##_set(vector, i, val);                                        \
		}                                                                          \
		vector->size = new_size;                                                   \
		vector->capacity = new_size;                                               \
	}                                                                                  \
                                                                                           \
	/* vector_size */                                                                  \
	/* gets the current size of the vector (number of elements actually                \
	 * being used)*/                                                                   \
	static inline size_t NAME##_size(const struct NAME *vector)                        \
	{                                                                                  \
		return vector->size;                                                       \
	}                                                                                  \
                                                                                           \
	/* vector_capacity */                                                              \
	/* gets the current capacity of the vector */                                      \
	static inline size_t NAME##_capacity(const struct NAME *vector)                    \
	{                                                                                  \
		return vector->capacity;                                                   \
	}                                                                                  \
                                                                                           \
	/* vector_pushback */                                                              \
	/*appends something (val) to the end of the size of the vector and                 \
	 * increases the vector's size by one. If vectoris too small, it                   \
	 * reallocates the vector so that it is 1.5x the original size  */                 \
	static inline void NAME##_push_back(struct NAME *vector,                           \
					    const TYPE val)                                \
	{                                                                                  \
		if (NAME##_size(vector) == NAME##_capacity(vector)) {                      \
			NAME##_reserve(vector, NAME##_capacity(vector) * 2);               \
		}                                                                          \
		NAME##_set(vector, NAME##_size(vector), val);                              \
		++vector->size;                                                            \
	}                                                                                  \
                                                                                           \
	/* vector_pop_back */                                                              \
	/* deletes the last element of the bector and returns the deleted                  \
	 * elment. Also reduces the size by 1. WARNING: does not do bounds                 \
	 * checking and will do strange things with empty vectors  */                      \
	static inline TYPE NAME##_pop_back(struct NAME *vector)                            \
	{                                                                                  \
		TYPE element = NAME##_get(vector, NAME##_size(vector) - 1);                \
		--vector->size;                                                            \
		return element;                                                            \
	}                                                                                  \
                                                                                           \
	/* vector_set */                                                                   \
	/*sets a specified index to a new value (val). WARNING: does not do                \
	 * bounds checking */                                                              \
	static inline void NAME##_set(struct NAME *vector, const size_t index,             \
				      const TYPE val)                                      \
	{                                                                                  \
		vector->data[index] = val;                                                 \
	}                                                                                  \
                                                                                           \
	/* vector_get */                                                                   \
	/*gets the specified index of an element. WARNING does not do bounds               \
	 * checking   */                                                                   \
	static inline TYPE NAME##_get(const struct NAME *vector,                           \
				      const size_t index)                                  \
	{                                                                                  \
		return vector->data[index];                                                \
	}                                                                                  \
                                                                                           \
	/* vector_get_p*/                                                                  \
	/*gets the pointer to a specified index of an element. WARNING does                \
	 * not do bounds checking   */                                                     \
	static inline TYPE *NAME##_get_p(const struct NAME *const vector,                  \
					 const size_t index)                               \
	{                                                                                  \
		return vector->data + index;                                               \
	}                                                                                  \
                                                                                           \
	/* vector_swap */                                                                  \
	/* Swaps 2 specified indexes with each other.WARNING: Does not do                  \
	 * bounds checking */                                                              \
	static inline void NAME##_swap(                                                    \
		struct NAME *vector, const size_t index0, const size_t index1)             \
	{                                                                                  \
		TYPE tmp = NAME##_get(vector, index0);                                     \
		NAME##_set(vector, index0, NAME##_get(vector, index1));                    \
		NAME##_set(vector, index1, tmp);                                           \
	}                                                                                  \
                                                                                           \
	/* vector_swap_back */                                                             \
	/* Swaps the specified index with the last size index. WARNING: Does               \
	 * not do bounds checking */                                                       \
	static inline void NAME##_swap_back(struct NAME *vector,                           \
					    const size_t index)                            \
	{                                                                                  \
		NAME##_swap(vector, index, NAME##_size(vector) - 1);                       \
	}                                                                                  \
                                                                                           \
	/* vector_remove */                                                                \
	/*removes an element from the vector at and index and shifts all                   \
	 * elements to the right of it back 1. Reduces the size of the vector              \
	 * by one as well. WARNING does not do bounds checking   */                        \
	static inline void NAME##_remove(struct NAME *vector,                              \
					 const size_t index)                               \
	{                                                                                  \
		for (size_t i = index; i < NAME##_size(vector) - 1; ++i) {                 \
			NAME##_set(vector, i, NAME##_get(vector, i + 1));                  \
		}                                                                          \
		--vector->size;                                                            \
	}                                                                                  \
                                                                                           \
	/* vector_lazy_clear */                                                            \
	/*lazily clears a vector by setting the size back to 0*/                           \
	static inline void NAME##_lazy_clear(struct NAME *vector)                          \
	{                                                                                  \
		vector->size = 0;                                                          \
	}                                                                                  \
                                                                                           \
	/* vector_free */                                                                  \
	/*frees the memory allocated by the vector.       */                               \
	static inline void NAME##_free(struct NAME *vector)                                \
	{                                                                                  \
		free(vector->data);                                                        \
	}


#define VECTOR_INIT(TYPE) Vector_##TYPE##_t_init
#define VECTOR_RESERVE(TYPE) Vector_TYPE_t##_reserve
#define VECTOR_RESIZE(TYPE) Vector_TYPE_t##_resize
#define VECTOR_SIZE(TYPE) Vector_TYPE_t##_size
#define VECTOR_CAPACITY(TYPE) Vector_TYPE_t##_capacity
#define VECTOR_PUSH_BACK(TYPE) Vector_TYPE_t##_push_back
#define VECTOR_POP_BACK(TYPE) Vector_TYPE_t##_pop_back
#define VECTOR_SET(TYPE) Vector_TYPE_t##_set
#define VECTOR_GET(TYPE) Vector_TYPE_t##_get
#define VECTOR_GET_P(TYPE) Vector_TYPE_t##_get_p
#define VECTOR_SWAP(TYPE) Vector_TYPE_t##_swap
#define VECTOR_SWAP_BACK(TYPE) Vector_TYPE_t##_swap_back
#define VECTOR_REMOVE(TYPE) Vector_TYPE_t##_remove
#define VECTOR_LAZY_CLEAR(TYPE) Vector_TYPE_t##_lazy_clear
#define VECTOR_FREE(TYPE) Vector_TYPE_t##_free
