#include <string.h>

#include "mlib.h"
#include "mvector.h"
#include "minternals.h"

#ifndef MLIB_INCLUDED
#error Include the ``mlib.h'' file before including an other mlib file
#endif

MVECTOR_DECLARE(mchar)

typedef MVector_mchar_t MString_t;

// -----------------------------------------
//    Macros to rename functions
// -----------------------------------------

#define MSTRING_T_INIT MK_FUNC(MK_VEC(mchar), init)
#define MSTRING_T_RESERVE MK_FUNC(MK_VEC(mchar), reserve)
#define MSTRING_T_RESIZE MK_FUNC(MK_VEC(mchar), resize)
#define MSTRING_T_SIZE MK_FUNC(MK_VEC(mchar), size)
#define MSTRING_T_CAPACITY MK_FUNC(MK_VEC(mchar), capacity)
#define MSTRING_T_PUSH_BACK MK_FUNC(MK_VEC(mchar), push_back)
#define MSTRING_T_POP_BACK MK_FUNC(MK_VEC(mchar), pop_back)
#define MSTRING_T_SET_AT MK_FUNC(MK_VEC(mchar), set)
#define MSTRING_T_GET_AT MK_FUNC(MK_VEC(mchar), get)
#define MSTRING_T_GET_P_AT MK_FUNC(MK_VEC(mchar), get_p)
#define MSTRING_T_SET MK_FUNC(MK_VEC(mchar), set)
#define MSTRING_T_GET MK_FUNC(MK_VEC(mchar), get)
#define MSTRING_T_GET_P MK_FUNC(MK_VEC(mchar), get_p)
#define MSTRING_T_SWAP MK_FUNC(MK_VEC(mchar), swap)
#define MSTRING_T_SWAP_BACK MK_FUNC(MK_VEC(mchar), swap_back)
#define MSTRING_T_REMOVE MK_FUNC(MK_VEC(mchar), remove)
#define MSTRING_T_LAZY_CLEAR MK_FUNC(MK_VEC(mchar), lazy_clear)
#define MSTRING_T_FREE MK_FUNC(MK_VEC(mchar), free)

// -----------------------------------------
//    Extra functions
// -----------------------------------------


// initializes a string
static inline mvoid MK_FUNC(MString_t, init_with_mchar)(MString_t *str,
							mchar *val);

// copies string a to pointer b. Allocates b on the heap
// dest: must be an intialized string and copied string
// source: must be an intialized string
static inline mvoid MK_FUNC(MString_t, copy_t)(MString_t *dest,
					       const MString_t *source);

// copies char* b to String_t pointer a. Allocates b on the heap
// dest: must be an intialized string and copied string
// source: must be an intialized string
static inline mvoid MK_FUNC(MString_t, copy_mcharptr)(MString_t *dest,
						      const mcharptr source);

// compares to see if the strings are equal
// a: must be an intialized string with contents
// b: must be an intialized string with contents
static inline mbool MK_FUNC(MString_t, is_equal)(const MString_t *a,
						 const MString_t *b);

// -----------------------------------------
//    Extra functions implementations
// -----------------------------------------
static inline mvoid MK_FUNC(MString_t, init_with_mcharptr)(MString_t *str,
							   mcharptr val)
{
	MSTRING_T_INIT(str, 1);
	MString_t_copy_mcharptr(str, val);
}
static inline mvoid MK_FUNC(MString_t, copy_string_t)(MString_t *dest,
						      const MString_t *source)
{
	msize sourceCapacity = MSTRING_T_CAPACITY(source);
	MSTRING_T_LAZY_CLEAR(dest);
	MSTRING_T_RESERVE(dest, sourceCapacity);

	msize sourceLen = MSTRING_T_SIZE(source);

	for (msize i = 0; i < sourceLen; ++i) {
		MSTRING_T_PUSH_BACK(dest, MSTRING_T_GET_AT(source, i));
	}
}

static inline mvoid MK_FUNC(MString_t, copy_mcharptr)(MString_t *dest,
						      const mcharptr source)
{

	msize sourceBufferSize = strlen(source) + 1;

	MSTRING_T_RESERVE(dest, sourceBufferSize);

	for (msize i = 0; i < sourceBufferSize; ++i) {
		MSTRING_T_PUSH_BACK(dest, source[i]);
	}
}

static inline mbool MK_FUNC(MString_t, is_equal)(const MString_t *a,
						 const MString_t *b)
{
	// size must be equal
	if (MSTRING_T_SIZE(a) != MSTRING_T_SIZE(b))
		return false;


	// testing equality of value
	msize len = MSTRING_T_SIZE(a);
	for (msize i = 0; i < len; ++i) {
		if (MSTRING_T_GET_AT(a, i) != MSTRING_T_GET_AT(b, i))
			return false;
	}

	return true;
}
