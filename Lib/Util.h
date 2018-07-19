#pragma once
#include <stdlib.h>
/**
 * Utility functions for this project
 */

// -----------------------------------------
//    Macros
// -----------------------------------------

// use MACRO_CONCAT to concatanate 2 macros together.
#define MCAT(a, b) MCAT_(a, b)
#define MCAT_(a, b) a##b

// -----------------------------------------
//    Procedures
// -----------------------------------------

// mallocs with error handling
void* safe_malloc(const size_t n);

// concats two strings by copying them to a new malloc'ed buffer. Remember to
// call "free" for the new string as they are allocated on the heap.
char* UTI_strcat(const char*, const char*);
