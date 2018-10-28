#include <string.h>

#include "mlib.h"
#include "mvector.h"
#include "minternals.h"

#ifndef MLIB_INCLUDED
#error Include the ``mlib.h'' file before including an other mlib file
#endif

#define MK_STR() String_t

VECTOR_TYPE_DECLARE(mchar, MK_STR())

// -----------------------------------------
//    Macros to rename functions
// -----------------------------------------

#define STRING_T_INIT MK_FUNC(MK_STR(), init)
#define STRING_T_RESERVE MK_FUNC(MK_STR(), reserve)
#define STRING_T_RESIZE MK_FUNC(MK_STR(), resize)
#define STRING_T_SIZE MK_FUNC(MK_STR(), size)
#define STRING_T_CAPACITY MK_FUNC(MK_STR(), capacity)
#define STRING_T_PUSH_BACK MK_FUNC(MK_STR(), push_back)
#define STRING_T_POP_BACK MK_FUNC(MK_STR(), pop_back)
#define STRING_T_SET_AT MK_FUNC(MK_STR(), set)
#define STRING_T_GET_AT MK_FUNC(MK_STR(), get)
#define STRING_T_GET_P_AT MK_FUNC(MK_STR(), get_p)
#define STRING_T_SET MK_FUNC(MK_STR(), set)
#define STRING_T_GET MK_FUNC(MK_STR(), get)
#define STRING_T_GET_P MK_FUNC(MK_STR(), get_p)
#define STRING_T_SWAP MK_FUNC(MK_STR(), swap)
#define STRING_T_SWAP_BACK MK_FUNC(MK_STR(), swap_back)
#define STRING_T_REMOVE MK_FUNC(MK_STR(), remove)
#define STRING_T_LAZY_CLEAR MK_FUNC(MK_STR(), lazy_clear)
#define STRING_T_FREE MK_FUNC(MK_STR(), free)

// -----------------------------------------
//    Extra functions
// -----------------------------------------

// copies string a to pointer b. Allocates b on the heap
// dest: must be an intialized string and copied string
// source: must be an intialized string
static inline mvoid MK_FUNC(MK_STR(),
			    copy_string_t)(struct MK_STR() * dest,
					   const struct MK_STR() * source);

// copies char* b to String_t pointer a. Allocates b on the heap
// dest: must be an intialized string and copied string
// source: must be an intialized string
static inline mvoid MK_FUNC(MK_STR(), copy_mcharptr)(struct MK_STR() * dest,
						     const mcharptr source);

// compares to see if the strings are equal
// a: must be an intialized string with contents
// b: must be an intialized string with contents
static inline mbool MK_FUNC(MK_STR(), is_equal)(const struct MK_STR() * a,
						const struct MK_STR() * b);

// -----------------------------------------
//    Extra functions implementations
// -----------------------------------------
static inline mvoid MK_FUNC(MK_STR(),
			    copy_string_t)(struct MK_STR() * dest,
					   const struct MK_STR() * source)
{
	msize sourceCapacity = STRING_T_CAPACITY(source);
	STRING_T_LAZY_CLEAR(dest);
	STRING_T_RESERVE(dest, sourceCapacity);

	msize sourceLen = STRING_T_SIZE(source);

	for (msize i = 0; i < sourceLen; ++i) {
		STRING_T_PUSH_BACK(dest, STRING_T_GET_AT(source, i));
	}
}

static inline mvoid MK_FUNC(MK_STR(), copy_mcharptr)(struct MK_STR() * dest,
						     const mcharptr source)
{

	msize sourceBufferSize = strlen(source) + 1;

	STRING_T_RESERVE(dest, sourceBufferSize);

	for (msize i = 0; i < sourceBufferSize; ++i) {
		STRING_T_PUSH_BACK(dest, source[i]);
	}
}

static inline mbool MK_FUNC(MK_STR(), is_equal)(const struct MK_STR() * a,
						const struct MK_STR() * b)
{
	// size must be equal
	if (STRING_T_SIZE(a) != STRING_T_SIZE(b))
		return false;


	// testing equality of value
	msize len = STRING_T_SIZE(a);
	for (msize i = 0; i < len; ++i) {
		if (STRING_T_GET_AT(a, i) != STRING_T_GET_AT(b, i))
			return false;
	}

	return true;
}
