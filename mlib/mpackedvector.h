#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mlib.h"
#include "mvector.h"


/**
 * Macros for a generic packed vector. Before using this, ensure that you create
 a vector with the same TYPE and PREFIX as the PackedVector.
 *
 * NOTE: this will declare a vector of the same type
 *
 * Specifcations are as follows:
 * sparse_vector: sparse vector that contains indexes to the index of the data
 in the packed_vector
 * next_packed_index: maintains the state of where to put the next val
 * packed_indices: indicies that allow the reverse O(1) lookup of the
 sparse_vector index of a val in the packed_data
 * packed_data: packed array of data for iteration
 *
 * functions:
 * add -> O(1) and placed unsorted in a contigious memory packed_vector
 * deletion -> O(1) utilizes pop and swap to be O(1) whilst having contigous
 memory in the packed_data vector
 */

// size_t vector
MVECTOR_DECLARE(msize)


// -----------------------------------------
//    Function interface
// -----------------------------------------
// TYPE must be not be a pointer. A typedeffed pointer is a workaround of this
#define PACKED_VECTOR_DECLARE(TYPE)                                            \
	PACKEDVECTOR_TYPE_DECLARE(TYPE, MK_PKD_VEC(TYPE))

// names the vector
#define MK_PKD_VEC(NAME) PackedVector_##NAME##_t

/* packedvector_init */
/* initializes the packedvector with a given capcity. Fills the
 * sparse_vectorwith null values. */
#define MPACKED_VECTOR_INIT(TYPE) MK_FUNC(MK_PKD_VEC(TYPE), init)
#define MPACKED_VECTOR_ADD_AT(TYPE) MK_FUNC(MK_PKD_VEC(TYPE), add_at)
#define MPACKED_VECTOR_REMOVE_AT(TYPE) MK_FUNC(MK_PKD_VEC(TYPE), remove_at)
#define MPACKED_VECTOR_GET_P_AT(TYPE) MK_FUNC(MK_PKD_VEC(TYPE), get_p_at)
#define MPACKED_VECTOR_GET_INDEX_FROM(TYPE)                                    \
	MK_FUNC(MK_PKD_VEC(TYPE), get_index_from)
#define MPACKED_VECTOR_FREE(TYPE) MK_FUNC(MK_PKD_VEC(TYPE), free)

// -----------------------------------------
//    Debug macros
// -----------------------------------------

// -----------------------------------------
//    Macro to generate
// -----------------------------------------
#define PACKEDVECTOR_TYPE_DECLARE(TYPE, NAME)                                  \
	/* Creates the necassary vector beforehand... */                       \
	VECTOR_DECLARE(TYPE)                                                   \
                                                                               \
	/* Types... */                                                         \
	/* --------------------- */                                            \
	struct NAME;                                                           \
	struct NAME {                                                          \
		struct MK_VEC(msize) sparse_vector;                            \
		size_t next_packed_index; /* next empty index in the packed    \
					     array */                          \
		struct MK_VEC(msize)                                           \
			packed_indices; /* index of the corrosponding          \
				packed_data in the sparse_vector*/             \
                                                                               \
		struct VECPREFIX##Vector                                       \
			packed_data; /* tightly packed array of the data */    \
	};                                                                     \
                                                                               \
	/* Procedures... */                                                    \
	/* --------------------- */                                            \
                                                                               \
	/* packedvector_init */                                                \
	/* initializes the packedvector with a given capcity. Fills the        \
	 * sparse_vectorwith null values. */                                   \
	void NAME##_init(struct NAME *packedvector, size_t capacity);          \
                                                                               \
	/* packedvector_add_at */                                              \
	/* at "index" in "sparse_vector," a size_t will point to the "val" in  \
	 * the tightly packed "packed_data" vector. Increases the              \
	 * "next_packed_index" by 1 as well. WARNING: Does minor bounds        \
	 * checking - if the desired index is out of bounds, it will realocate \
	 * so the vector is 1.5x the size of the required index. Also, it      \
	 * checks to see if the current index is free, so it will not add to   \
	 * the index UNLESS it is free.*/                                      \
	void NAME##_add_at(struct NAME *packedvector, const size_t index,      \
			   TYPE *val);                                         \
                                                                               \
	/* packedvector_remove_at */                                           \
	/* remove the component in the packed array "packed_data" by           \
	 * vector_swap_back and vector_pop_back. Reduces "next_packed_index"   \
	 * by 1 as well as sets the sparse_vector's "index" to size_t max to   \
	 * denote that it no longer exists. It will not remove an index that   \
	 * is already removed */                                               \
	void NAME##_remove_at(struct NAME *packedvector, size_t index);        \
                                                                               \
	/* packedvector_get_packed_data */                                     \
	/* returns a const pointer to the vector of the packed_data */         \
	const struct VECPREFIX##Vector *NAME##_get_packed_data(                \
		const struct NAME *packedvector);                              \
                                                                               \
	/* packedvector_get_p_at */                                            \
	/* at index, it will return a pointerto the packed_data it corrosponds \
	 * to. If it is out of bounds, or there is no data for that point, it  \
	 * will return NULL. This allows the data to be modifed. "index"       \
	 * refers to the sparse_vector that entity is known as */              \
	TYPE *NAME##_get_p_at(struct NAME *packedvector, size_t index);        \
                                                                               \
	/* packedvector_get_index_from */                                      \
	/* at "index" for the packed data vector(packed_data), it will return  \
	 * the corrosponding sparse_vector index. WARNING: Does not do bounds  \
	 * checking                                                            \
	 * TODO WRITE UNIT TESTS FOR THIS                                      \
	 */                                                                    \
	size_t NAME##_get_index_from(const struct NAME *packedvector,          \
				     size_t index);                            \
                                                                               \
	/* packedvector_free */                                                \
	/* frees the PackedVector*/                                            \
	void NAME##_free(struct NAME *packedvector);                           \
                                                                               \
                                                                               \
	/* Implementations... */                                               \
	/* --------------------- */                                            \
	/* packedvector_init */                                                \
	void NAME##_init(struct NAME *packedvector, size_t capacity)           \
	{                                                                      \
		/* setting the sparse vector to the capacity with SIZE_MAX as  \
		 * the default value */                                        \
		VECTOR_INIT(msize)(&packedvector->sparse_vector);              \
		VECTOR_RESIZE(msize)                                           \
		(&packedvector->sparse_vector, capacity, SIZE_MAX);            \
                                                                               \
		/*setting the next index to 0*/                                \
		packedvector->next_packed_index = 0;                           \
                                                                               \
		/* reserving the data for the global indices and data*/        \
		VECTOR_INIT(msize)(&packedvector->packed_indices);             \
		VECTOR_RESERVE(msize)                                          \
		(&packedvector->packed_indices, capacity);                     \
                                                                               \
		VECPREFIX##Vector_init(&packedvector->packed_data);            \
		VECPREFIX##Vector_reserve(&packedvector->packed_data,          \
					  capacity);                           \
	}                                                                      \
                                                                               \
	/* packedvector_add_at */                                              \
	void NAME##_add_at(struct NAME *packedvector, const size_t index,      \
			   TYPE *val)                                          \
	{                                                                      \
		/* if the desired index is outside of the                      \
		 * sparse_vector, it                                           \
		 * will resize itself to be 1.5X the index */                  \
		if (index                                                      \
		    >= VECTOR_CAPACITY(msize)(&packedvector->sparse_vector)) { \
			VECTOR_RESIZE(msize)                                   \
			(&packedvector->sparse_vector, index * 1.5, SIZE_MAX); \
		}                                                              \
		/*checks to see if it is actually a free index before adding   \
		 * the val to the packedvector*/                               \
		if (VECTOR_GET(msize)(&packedvector->sparse_vector, index)     \
		    == SIZE_MAX) {                                             \
			VECTOR_SET(msize)                                      \
			(&packedvector->sparse_vector, index,                  \
			 packedvector->next_packed_index);                     \
                                                                               \
			VECTOR_PUSH_BACK(msize)                                \
			(&packedvector->packed_indices, index);                \
			VECPREFIX##Vector_push_back(                           \
				&packedvector->packed_data, *val);             \
			/* increases the next index by one, so that            \
			 * the next add will push_back */                      \
			++packedvector->next_packed_index;                     \
		}                                                              \
	}                                                                      \
                                                                               \
	/* packedvector_remove_at */                                           \
	void NAME##_remove_at(struct NAME *packedvector, size_t index)         \
	{                                                                      \
		/* ensures that we only remove free indicies / in bound        \
		 * indicies */                                                 \
		if (index < VECTOR_SIZE(msize)(&packedvector->sparse_vector)   \
		    && VECTOR_GET(msize)(&packedvector->sparse_vector, index)  \
			       != SIZE_MAX) {                                  \
			/*if there is only 1 index left, just pop_back it from \
			 * the vectors*/                                       \
			if (VECTOR_SIZE(msize)(&packedvector->packed_indices)  \
			    == 1) {                                            \
				/* setting the sparse_vector index to SIZE_MAX \
				 */                                            \
				VECTOR_SET(msize)                              \
				(&packedvector->sparse_vector, index,          \
				 SIZE_MAX);                                    \
                                                                               \
				/* Popping the unused data at the end of the   \
				 * densely packed vectors */                   \
				VECTOR_POP_BACK(msize)                         \
				(&packedvector->packed_indices);               \
				VECPREFIX##Vector_pop_back(                    \
					&packedvector->packed_data);           \
			} else {                                               \
				size_t lastSparseVectorIndex = VECTOR_GET(     \
					msize)(                                \
					&packedvector->packed_indices,         \
					VECTOR_SIZE(msize)(                    \
						&packedvector->packed_indices) \
						- 1);                          \
                                                                               \
				size_t internalIndex = VECTOR_GET(msize)(      \
					&packedvector->sparse_vector, index);  \
				/*swapping the sparse vector */                \
				VECTOR_SWAP(msize)                             \
				(&packedvector->sparse_vector, index,          \
				 lastSparseVectorIndex);                       \
                                                                               \
				/* swapping the global indices and packed data \
				 * vector*/                                    \
				VECTOR_SWAP_BACK(msize)                        \
				(&packedvector->packed_indices,                \
				 internalIndex);                               \
				VECPREFIX##Vector_swap_back(                   \
					&packedvector->packed_data,            \
					internalIndex);                        \
                                                                               \
				/* setting the sparse_vector index to SIZE_MAX \
				 */                                            \
				VECTOR_SET(msize)                              \
				(&packedvector->sparse_vector, index,          \
				 SIZE_MAX);                                    \
                                                                               \
				/* Popping the unused data at the end of the   \
				 * densely packed vectors */                   \
				VECTOR_POP_BACK(msize)                         \
				(&packedvector->packed_indices);               \
				VECPREFIX##Vector_pop_back(                    \
					&packedvector->packed_data);           \
			}                                                      \
			/* required so the add function works properly*/       \
			--packedvector->next_packed_index;                     \
		}                                                              \
	}                                                                      \
                                                                               \
	/* packedvector_get_packed_data */                                     \
	const struct VECPREFIX##Vector *NAME##_get_packed_data(                \
		const struct NAME *packedvector)                               \
	{                                                                      \
		return &packedvector->packed_data;                             \
	}                                                                      \
                                                                               \
	/* packedvector_get_p_at */                                            \
	TYPE *NAME##_get_p_at(struct NAME *packedvector, size_t index)         \
	{                                                                      \
		if (index >= VECTOR_SIZE(msize)(&packedvector->sparse_vector)  \
		    || VECTOR_GET(msize)(&packedvector->sparse_vector, index)  \
			       == SIZE_MAX) {                                  \
			return NULL;                                           \
		} else {                                                       \
			size_t dataIndex = VECTOR_GET(msize)(                  \
				&packedvector->sparse_vector, index);          \
			return packedvector->packed_data.data + dataIndex;     \
		}                                                              \
	}                                                                      \
                                                                               \
	/* packedvector_get_index_from */                                      \
	size_t NAME##_get_index_from(const struct NAME *packedvector,          \
				     size_t index)                             \
	{                                                                      \
		return VECTOR_GET(msize)(&packedvector->packed_indices,        \
					 index);                               \
	}                                                                      \
                                                                               \
	/* packedvector_free */                                                \
	/* frees the data in the packedvectors*/                               \
	void NAME##_free(struct NAME *packedvector)                            \
	{                                                                      \
		VECTOR_FREE(msize)(&packedvector->sparse_vector);              \
		VECTOR_FREE(msize)(&packedvector->packed_indices);             \
		VECPREFIX##Vector_free(&packedvector->packed_data);            \
	}
