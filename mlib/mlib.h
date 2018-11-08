#pragma once
#include <stdbool.h>
#include <stdlib.h>

/** mlib -- Minature Spork. Generic data structure macros.
 * This header MUST be included before any other of the libraries data
 * structures. Or else an error will be thrown.
 *
 */

#define MLIB_INCLUDED TRUE

// comment to remove debugging
#define MLIB_DEBUG TRUE

// -----------------------------------------
//    Types
// -----------------------------------------

typedef bool mbool;
typedef void mvoid;
typedef void *mvoidptr;
typedef const void *mvoidconstptr;

typedef char mchar;
typedef char *mcharptr;
typedef unsigned char muchar;

typedef int mint;
typedef unsigned int muint;
typedef int mint;
typedef short mshort;
typedef unsigned short mushort;
typedef long mlong;
typedef unsigned long mulong;
typedef float mfloat;
typedef double mdouble;

typedef size_t msize;
