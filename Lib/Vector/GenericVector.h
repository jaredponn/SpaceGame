#pragma once
#include <stdlib.h>
#include "../Util.h"

/**
 * Declarations for a vector (a wrapper for a continious memory object). Not C++
 * standard compliant.
 */

// -----------------------------------------
//    Macros
// -----------------------------------------

// replaces GENERICTYPE with TYPE if TYPE is defined
#ifdef TYPE
#define GENERICTYPE TYPE

// if TYPED is defined it prefixes the procedures and structs with the TYPED
// label

#ifdef TYPED

#define Vector MACRO_CONCAT(TYPED, _Vector)
#define vector_new MACRO_CONCAT(TYPED, _vector_new)
#define vector_init MACRO_CONCAT(TYPED, _vector_init)
#define vector_reserve MACRO_CONCAT(TYPED, _vector_reserve)
#define vector_resize MACRO_CONCAT(TYPED, _vector_resize)
#define vector_size MACRO_CONCAT(TYPED, _vector_size)
#define vector_capacity MACRO_CONCAT(TYPED, _vector_capacity)
#define vector_pushback MACRO_CONCAT(TYPED, _vector_pushback)
#define vector_set MACRO_CONCAT(TYPED, _vector_set)
#define vector_get MACRO_CONCAT(TYPED, _vector_get)
#define vector_remove MACRO_CONCAT(TYPED, _vector_remove)
#define vector_free MACRO_CONCAT(TYPED, _vector_free)

// -----------------------------------------
//    Types
// -----------------------------------------

struct Vector;

struct Vector {
        size_t size;        // size of the memory in use
        size_t capacity;    // total capacity of the vector
        GENERICTYPE* data;  // data of the vector
};

// -----------------------------------------
//    Procedures
// -----------------------------------------

// creates a new vector
struct Vector* vector_new(void);

// intializes a new vector
void vector_init(struct Vector* vector);

// changes the capacity of a vector to whatever given capacity
void vector_reserve(struct Vector* vector, size_t new_capacity);

// resizes vector to the new size (and reallocates) and gives it a default value
void vector_resize(struct Vector* vector, size_t new_size, GENERICTYPE val);

// gets the size of the vector
size_t vector_size(struct Vector* vector);

// gets the total capacity
size_t vector_capacity(struct Vector* vector);

// appends something to the end of the size of the vector and increases size by
// 1. If the vector is too small, it reallocates it so it is 1.5x the original
// size
void vector_pushback(struct Vector* vector, GENERICTYPE val);

// sets a specified inddex to a new elment
// unsafe without bounds checking
void vector_set(struct Vector*, size_t index, GENERICTYPE val);

// gets a specified inddex to a new elment
// unsafe without bounds checking
GENERICTYPE vector_get(struct Vector*, size_t index);

// deletes an elment from a vector and shifts all elments to the right of it
// back 1
// unsafe without bounds checking
void vector_remove(struct Vector*, size_t index);

// frees the entire vector
void vector_free(struct Vector*);

#endif  // TYPED
#endif  // TYPE
