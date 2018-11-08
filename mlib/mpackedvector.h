#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mlib.h"
#include "mvector.h"
#include "msize_vector.h"


/**
 * Macros for a generic packed vector.
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


// -----------------------------------------
//    Function interface
// -----------------------------------------
// TYPE must be not be a pointer. A typedeffed pointer is a workaround of this
#define MPACKED_VECTOR_DECLARE(TYPE) MPACKED_VECTOR_TYPE_DECLARE(TYPE)

// names the vector
#define MK_PKD_VEC(NAME) MPackedVector_##NAME##_t

/* packedvector_init(PackedVector, msize capacity) */
/* initializes the packedvector with a given capcity. Fills the
 * sparse_vector with SIZE_MAX. */
#define MPACKED_VECTOR_INIT(TYPE) MK_FUNC(MK_PKD_VEC(TYPE), init)

/* packedvector_add_at_sparse_vector(PackedVector, msize index, TYPE val) */
/* Adds an index at the sparse vector, while putting the actual TYPE val in the
 * packed vector, with its corrosponding index in the packed_indicies vector.*/
/* at "index" in "sparse_vector," a msize will point to the "val" in  \
 * the tightly packed "packed_data" vector. Increases the              \
 * "next_packed_index" by 1 as well. WARNING: Does minor bounds        \
 * checking - if the desired index is out of bounds, it will realocate \
 * so the vector is 1.5x the size of the required index. Also, it      \
 * checks to see if the current index is free, so it will not add to   \
 * the index UNLESS it is free.*/
#define MPACKED_VECTOR_ADD_AT_SPARSE_VECTOR(TYPE)                              \
	MK_FUNC(MK_PKD_VEC(TYPE), add_at_sparse_vector)

/* packedvector_remove_at_sparse_vector(PackedVector, msize index) */
/*at an index in the sparse vector, it will remove it by marking it with
 * SIZE_MAX, and doing a push / swap back for the packed vectors to remove it.
 * It reduces the "next_packed_index" by one as well. This system will not
 * remove an index that is already removed*/
#define MPACKED_VECTOR_REMOVE_AT_SPARSE_VECTOR(TYPE)                           \
	MK_FUNC(MK_PKD_VEC(TYPE), remove_at_sparse_vector)

/* packedvector_get_data_from_sparse_vector(PackedVetor, msize index) */
/* at an index of the the sparse vector, returns the a copy of the packed data
 * at that point Does not do any bounds checking*/
#define MPACKED_VECTOR_GET_DATA_FROM_SPARSE_VECTOR(TYPE)                       \
	MK_FUNC(MK_PKD_VEC(TYPE), get_data_from_sparse_vector)

/* packedvector_get_p_at_sparse_vector(PackedVetor, msize index) */
/* at an index of the the sparse vector, returns the a the pointer of the packed
 * data at that point Does not do any bounds checking*/
#define MPACKED_VECTOR_GET_P_FROM_SPARSE_VECTOR(TYPE)                          \
	MK_FUNC(MK_PKD_VEC(TYPE), get_p_from_sparse_vector)

/* packedvector_get_at_packed_data(PackedVetor, msize index) */
/* at an index of the packed data, returns the a copy of the packed data. Does
 * not do any bounds checking*/
#define MPACKED_VECTOR_GET_AT_PACKED_DATA(TYPE)                                \
	MK_FUNC(MK_PKD_VEC(TYPE), get_at_packed_data)

/* packedvector_get_p_at_packed_data(PackedVetor, msize index) */
/* at an index of the packed vector, returns the pointer of the packed data.
 * Does not do any bounds checking*/
#define MPACKED_VECTOR_GET_P_AT_PACKED_DATA(TYPE)                              \
	MK_FUNC(MK_PKD_VEC(TYPE), get_p_at_packed_data)

/* packed_vector_get_index_from_packed_data(PackedVector, msize index)*/
/* at "index" in the packed data vector, it will return the the index of the
 * packed data in the sparse vector */
#define MPACKED_VECTOR_GET_INDEX_FROM_PACKED_DATA(TYPE)                        \
	MK_FUNC(MK_PKD_VEC(TYPE), get_index_from_packed_data)

/* packedvector_set_at_packed_data(PackedVector, msize index, val)
   at "index" in the packed data vector, it will copy the "val" into that index.
   Does not do bounds checking. */
#define MPACKED_VECTOR_SET_AT_PACKED_DATA(TYPE)                                \
	MK_FUNC(MK_PKD_VEC(TYPE), set_at_packed_data);


/* packed_vector_free(PackedVector)*/
/* at "index" in the packed data vector, it will return the the index of the
 * packed data in the sparse vector */
#define MPACKED_VECTOR_FREE(TYPE) MK_FUNC(MK_PKD_VEC(TYPE), free)

// -----------------------------------------
//    Debug macros
// -----------------------------------------
/* if MLIB_DEBUG is enabled, then include the debug macros */
#ifdef MLIB_DEBUG
// asserts that the inital capacity of a vector must be greater than 0
#define DBG_PKD_PACKED_VECTOR_ADD_AT_SPARSE_VECTOR_ALREADY_ADDED_ASSERTION()                \
	if (capacity <= 0) {                                                                \
		printf("MLIB VECTOR_INIT ERROR AT FILE: " GET_FILE_NAME()                 \
		       ". Initial capacity must be greater than 0.\nAborting... \n"); \
		abort();                                                                    \
	}

/* otherwise do not include the extra dubggin checks */
#else
#define DBG_PKD_PACKED_VECTOR_ADD_AT_SPARSE_VECTOR_ALREADY_ADDED_ASSERTION()
#endif

// -----------------------------------------
//    Macro to generate
// -----------------------------------------
#define MPACKED_VECTOR_TYPE_DECLARE(TYPE)                                      \
	/* Creates the necassary vector beforehand... */                       \
	MVECTOR_DECLARE(TYPE)                                                  \
                                                                               \
	/* Types... */                                                         \
	/* --------------------- */                                            \
	typedef struct MK_PKD_VEC(TYPE) {                                      \
		struct MK_VEC(msize)                                           \
			sparse_vector; /*indicies to the packed_data and       \
					  packed_indicies*/                    \
		struct MK_VEC(msize)                                           \
			packed_indices; /* index of the corrosponding          \
				packed_data in the sparse_vector*/             \
		struct MK_VEC(TYPE)                                            \
			packed_data; /* tightly packed array of the data */    \
		msize next_packed_index; /* next empty index in the packed     \
					     array */                          \
	} MK_PKD_VEC(TYPE);                                                    \
                                                                               \
	/* Procedures... */                                                    \
	/* --------------------- */                                            \
                                                                               \
	/* packedvector_init */                                                \
	static inline void MK_FUNC(MK_PKD_VEC(TYPE), init)(                    \
		struct MK_PKD_VEC(TYPE) * packedvector, msize capacity);       \
                                                                               \
	/* packedvector_add_at_sparse_vector */                                \
	static inline void MK_FUNC(MK_PKD_VEC(TYPE), add_at_sparse_vector)(    \
		MK_PKD_VEC(TYPE) * packedvector, const msize index, TYPE val); \
                                                                               \
	/* packedvector_get_data_from_sparse_vector */                         \
	static inline TYPE MK_FUNC(MK_PKD_VEC(TYPE),                           \
				   get_data_from_sparse_vector)(               \
		struct MK_PKD_VEC(TYPE) * packedvector, const msize index);    \
                                                                               \
	/* packedvector_get_data_p_from_sparse_vector */                       \
	static inline TYPE *MK_FUNC(MK_PKD_VEC(TYPE),                          \
				    get_data_p_from_sparse_vector)(            \
		MK_PKD_VEC(TYPE) * packedvector, const msize index);           \
                                                                               \
	/* packedvector_remove_at_sparse_vector */                             \
	static inline void MK_FUNC(MK_PKD_VEC(TYPE), remove_at_sparse_vector)( \
		struct MK_PKD_VEC(TYPE) * packedvector, msize index);          \
                                                                               \
	/* packedvector_set_at_packed_data */                                  \
	static inline void MK_FUNC(MK_PKD_VEC(TYPE), set_at_packed_data)(      \
		const MK_PKD_VEC(TYPE) * packedvector, msize index, TYPE val); \
                                                                               \
	/* packedvector_get_at_packed_data */                                  \
	static inline TYPE MK_FUNC(MK_PKD_VEC(TYPE), get_at_packed_data)(      \
		const MK_PKD_VEC(TYPE) * packedvector, msize index);           \
                                                                               \
	/* packedvector_get_p_at_packed_data */                                \
	static inline const TYPE *MK_FUNC(MK_PKD_VEC(TYPE),                    \
					  get_p_at_packed_data)(               \
		const struct MK_PKD_VEC(TYPE) * packedvector, msize index);    \
                                                                               \
                                                                               \
	/* packedvector_get_index_from_packed_data */                          \
	static inline msize MK_FUNC(MK_PKD_VEC(TYPE),                          \
				    get_index_from_packed_data)(               \
		const MK_PKD_VEC(TYPE) * packedvector, msize index);           \
                                                                               \
	/* packedvector_free */                                                \
	static inline void MK_FUNC(MK_PKD_VEC(TYPE), free)(                    \
		struct MK_PKD_VEC(TYPE) * packedvector);                       \
                                                                               \
                                                                               \
	/* Implementations... */                                               \
	/* --------------------- */                                            \
	/* packedvector_init */                                                \
	static inline void MK_FUNC(MK_PKD_VEC(TYPE), init)(                    \
		struct MK_PKD_VEC(TYPE) * packedvector, msize capacity)        \
	{                                                                      \
		/* setting the sparse vector to the capacity with SIZE_MAX as  \
		 * the default value that maps things over */                  \
		MVECTOR_INIT(msize)(&packedvector->sparse_vector, capacity);   \
		MVECTOR_FILL(msize)                                            \
		(&packedvector->sparse_vector, SIZE_MAX);                      \
                                                                               \
		/*setting the next index to 0*/                                \
		packedvector->next_packed_index = 0;                           \
                                                                               \
		/* reserving the data for the global indices and data*/        \
		MVECTOR_INIT(msize)(&packedvector->packed_indices, capacity);  \
                                                                               \
		/* reserving the data for the packed data*/                    \
		MVECTOR_INIT(TYPE)(&packedvector->packed_data, capacity);      \
	}                                                                      \
                                                                               \
	/* packedvector_add_at */                                              \
	static inline void MK_FUNC(MK_PKD_VEC(TYPE), add_at_sparse_vector)(    \
		struct MK_PKD_VEC(TYPE) * packedvector, const msize index,     \
		TYPE val)                                                      \
	{                                                                      \
		/* if the desired index is outside of the                      \
		 * sparse_vector, it                                           \
		 * will resize itself to be 1.5X the index */                  \
		if (index >= MVECTOR_CAPACITY(msize)(                          \
				     &packedvector->sparse_vector)) {          \
			MVECTOR_RESIZE(msize)                                  \
			(&packedvector->sparse_vector, index * 1.5, SIZE_MAX); \
		}                                                              \
		/*checks to see if it is actually a free index before adding   \
		 * the val to the packedvector*/                               \
		if (MVECTOR_GET(msize)(&packedvector->sparse_vector, index)    \
		    == SIZE_MAX) {                                             \
			MVECTOR_SET(msize)                                     \
			(&packedvector->sparse_vector, index,                  \
			 packedvector->next_packed_index);                     \
                                                                               \
			MVECTOR_PUSH_BACK(msize)                               \
			(&packedvector->packed_indices, index);                \
			MVECTOR_PUSH_BACK(TYPE)                                \
			(&packedvector->packed_data, val);                     \
                                                                               \
			/* increases the next index by one, so that            \
			 * the next add will push_back */                      \
			++packedvector->next_packed_index;                     \
		}                                                              \
	}                                                                      \
                                                                               \
	/* packedvector_remove_at */                                           \
	static inline void MK_FUNC(MK_PKD_VEC(TYPE), remove_at_sparse_vector)( \
		struct MK_PKD_VEC(TYPE) * packedvector, msize index)           \
	{                                                                      \
		/* ensures that we only remove free indicies / in bound        \
		 * indicies */                                                 \
		if (index < MVECTOR_SIZE(msize)(&packedvector->sparse_vector)  \
		    && MVECTOR_GET(msize)(&packedvector->sparse_vector, index) \
			       != SIZE_MAX) {                                  \
			/*if there is only 1 index left, just pop_back it from \
			 * the vectors*/                                       \
			if (MVECTOR_SIZE(msize)(&packedvector->packed_indices) \
			    == 1) {                                            \
				/* setting the sparse_vector index to SIZE_MAX \
				 */                                            \
				MVECTOR_SET_AT(msize)                          \
				(&packedvector->sparse_vector, index,          \
				 SIZE_MAX);                                    \
                                                                               \
				/* Popping the unused data at the end of the   \
				 * densely packed vectors */                   \
				MVECTOR_POP_BACK(msize)                        \
				(&packedvector->packed_indices);               \
				MVECTOR_POP_BACK(TYPE)                         \
				(&packedvector->packed_data);                  \
			} else {                                               \
				msize lastSparseVectorIndex = MVECTOR_GET(     \
					msize)(                                \
					&packedvector->packed_indices,         \
					MVECTOR_SIZE(msize)(                   \
						&packedvector->packed_indices) \
						- 1);                          \
                                                                               \
				msize internalIndex = MVECTOR_GET(msize)(      \
					&packedvector->sparse_vector, index);  \
				/*swapping the sparse vector */                \
				MVECTOR_SWAP(msize)                            \
				(&packedvector->sparse_vector, index,          \
				 lastSparseVectorIndex);                       \
                                                                               \
				/* swapping the global indices and packed data \
				 * vector*/                                    \
				MVECTOR_SWAP_BACK(msize)                       \
				(&packedvector->packed_indices,                \
				 internalIndex);                               \
				MVECTOR_SWAP_BACK(TYPE)                        \
				(&packedvector->packed_data, internalIndex);   \
                                                                               \
				/* setting the sparse_vector index to SIZE_MAX \
				 */                                            \
				MVECTOR_SET(msize)                             \
				(&packedvector->sparse_vector, index,          \
				 SIZE_MAX);                                    \
                                                                               \
				/* Popping the unused data at the end of the   \
				 * densely packed vectors */                   \
				MVECTOR_POP_BACK(msize)                        \
				(&packedvector->packed_indices);               \
				MVECTOR_POP_BACK(TYPE)                         \
				(&packedvector->packed_data);                  \
			}                                                      \
			/* required so the add function works properly*/       \
			--packedvector->next_packed_index;                     \
		}                                                              \
	}                                                                      \
                                                                               \
	/* packedvector_get_packed_data */                                     \
	static inline const struct MK_VEC(TYPE)                                \
		* MK_FUNC(MK_PKD_VEC(TYPE), get_packed_data_vector)(           \
			  const struct MK_PKD_VEC(TYPE) * packedvector)        \
	{                                                                      \
		return &packedvector->packed_data;                             \
	}                                                                      \
                                                                               \
	/* packedvector_get_p_at */                                            \
	static inline TYPE *MK_FUNC(MK_PKD_VEC(TYPE),                          \
				    get_data_p_from_sparse_vector)(            \
		struct MK_PKD_VEC(TYPE) * packedvector, msize index)           \
	{                                                                      \
		if (index >= MVECTOR_SIZE(msize)(&packedvector->sparse_vector) \
		    || MVECTOR_GET(msize)(&packedvector->sparse_vector, index) \
			       == SIZE_MAX) {                                  \
			return NULL;                                           \
		} else {                                                       \
			msize dataIndex = MVECTOR_GET_AT(msize)(               \
				&packedvector->sparse_vector, index);          \
			return packedvector->packed_data.data + dataIndex;     \
		}                                                              \
	}                                                                      \
                                                                               \
	/* packedvector_get_index_from */                                      \
	static inline msize MK_FUNC(MK_PKD_VEC(TYPE), get_index_from)(         \
		const struct MK_PKD_VEC(TYPE) * packedvector, msize index)     \
	{                                                                      \
		return MVECTOR_GET(msize)(&packedvector->packed_indices,       \
					  index);                              \
	}                                                                      \
                                                                               \
	/* packedvector_get_data_from_sparse_vector */                         \
	static inline TYPE MK_FUNC(MK_PKD_VEC(TYPE),                           \
				   get_data_from_sparse_vector)(               \
		struct MK_PKD_VEC(TYPE) * packedvector, const msize index)     \
	{                                                                      \
		msize packedVectorIndex = MVECTOR_GET_AT(msize)(               \
			&packedvector->sparse_vector, index);                  \
                                                                               \
		return MVECTOR_GET_AT(TYPE)(&packedvector->packed_data,        \
					    packedVectorIndex);                \
	}                                                                      \
                                                                               \
	/* packedvector_get_index_from_packed_data */                          \
	static inline msize MK_FUNC(MK_PKD_VEC(TYPE),                          \
				    get_index_from_packed_data)(               \
		const MK_PKD_VEC(TYPE) * packedvector, msize index)            \
	{                                                                      \
		return MVECTOR_GET_AT(msize)(&packedvector->packed_indices,    \
					     index);                           \
	}                                                                      \
                                                                               \
	/* packedvector_get_p_at_packed_data */                                \
	static inline const TYPE *MK_FUNC(MK_PKD_VEC(TYPE),                    \
					  get_p_at_packed_data)(               \
		const struct MK_PKD_VEC(TYPE) * packedvector, msize index)     \
	{                                                                      \
		return packedvector->packed_data.data + index;                 \
	}                                                                      \
                                                                               \
	/* packedvector_get_at_packed_data */                                  \
	static inline TYPE MK_FUNC(MK_PKD_VEC(TYPE), get_at_packed_data)(      \
		const MK_PKD_VEC(TYPE) * packedvector, msize index)            \
	{                                                                      \
		return packedvector->packed_data.data[index];                  \
	}                                                                      \
                                                                               \
                                                                               \
	/* packedvector_set_at_packed_data */                                  \
	static inline void MK_FUNC(MK_PKD_VEC(TYPE), set_at_packed_data)(      \
		const MK_PKD_VEC(TYPE) * packedvector, msize index, TYPE val)  \
	{                                                                      \
		packedvector->packed_data.data[index] = val;                   \
	}                                                                      \
                                                                               \
	/* packedvector_free */                                                \
	/* frees the data in the packedvectors*/                               \
	static inline void MK_FUNC(MK_PKD_VEC(TYPE), free)(                    \
		struct MK_PKD_VEC(TYPE) * packedvector)                        \
	{                                                                      \
		MVECTOR_FREE(msize)(&packedvector->sparse_vector);             \
		MVECTOR_FREE(msize)(&packedvector->packed_indices);            \
		MVECTOR_FREE(TYPE)(&packedvector->packed_data);                \
	}
