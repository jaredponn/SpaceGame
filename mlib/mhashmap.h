#include "mlib.h"
#include "mvector.h"
#include "mstring.h"

#ifndef MLIB_INCLUDED
#error Include the ``mlib.h'' file before including an other mlib file
#endif
/** mhashmap.h -- declarations for a string to another generic type
 * hashmap
 *
 */
#define HASHMAP_DECLARE(VALTYPE, NAME)                                         \
	HASHMAP_TYPE_DECLARE(VALTYPE, MK_HASHMAP(VALTYPE))

#define MK_HASHMAP(VALTYPE) Hashmap_##VALTYPE##_t

// -----------------------------------------
//    Functions
// -----------------------------------------

// initlizes a hash map.
// Types:: VALTYPE
// Function  params: Hashmap* (unitilized pointer), msize (size of hashmap)
#define HASHMAP_INIT(VALTYPE) MK_FUNC(MK_HASHMAP(VALTYPE), init)

// puts an element in the hashmp
// Types:: VALTYPE
// Function  params: Hashmap* (unitilized pointer), msize index to set
#define HASHMAP_INSERT(VALTYPE) MK_FUNC(MK_HASHMAP(VALTYPE), insert)

// gets an element of a hashmap
// Types:: , VALTYPE
// Function  params: Hashmap* (unitilized pointer), msize index to set
#define HASHMAP_GET_AT(VALTYPE) MK_FUNC(MK_HASHMAP(VALTYPE), get_at)

// resizes the hashmap
// Types:: , VALTYPE
// Function  params: Hashmap* (unitilized pointer), msize index to set
#define HASHMAP_RESIZE(VALTYPE) MK_FUNC(MK_HASHMAP(VALTYPE), resize)

// resizes the hashmap
// Types:: , VALTYPE
// Function  params: Hashmap* (unitilized pointer), msize index to set
#define HASHMAP_DELETE_AT(VALTYPE) MK_FUNC(MK_HASHMAP(VALTYPE), delete_at)

// frees the hashmap
// Types:: , VALTYPE
// Function  params: Hashmap* (unitilized pointer), msize (size of hashmap)
#define HASHMAP_FREE(VALTYPE) MK_FUNC(MK_HASHMAP(VALTYPE), free)

// -----------------------------------------
//    Macro to generate the functions
// -----------------------------------------

#define HASHMAP_TYPE_DECLARE(VALTYPE, NAME)                                    \
	/* Types... */                                                         \
	/* --------------------- */                                            \
	/* internal type -- a pair of the val with the key */                  \
	struct _hash_node_##VALTYPE {                                          \
		struct MK_STR() key;                                           \
		VALTYPE val;                                                   \
	};                                                                     \
                                                                               \
	/* declaring the proper vector */                                      \
	VECTOR_DECLARE(_hash_node_##VALTYPE)                                   \
                                                                               \
	/* hashmap type */                                                     \
	struct NAME {                                                          \
		MK_VECTOR(_hash_node_##VALTYPE) data;                          \
	};                                                                     \
	\
