#pragma once
#include <stdlib.h>
/**
 * Utility functions for this project
 */

// -----------------------------------------
//    Macros
// -----------------------------------------

// use MACRO_CONCAT to concatanate 2 macros together.
#define MACRO_CONCAT(_a, _b) MACRO_CONCAT_(_a, _b)
#define MACRO_CONCAT_(_a, _b) _a##_b

// -----------------------------------------
//    Procedures
// -----------------------------------------

// mallocs with error handling
void* safe_malloc(const size_t n);

// concats two strings by copying them to a new malloc'ed buffer. Remember to
// call "free" for the new string as they are allocated on the heap.
char* UTI_strcat(const char*, const char*);
