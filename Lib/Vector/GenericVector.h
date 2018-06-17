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

// TODO

// -----------------------------------------
//    Types
// -----------------------------------------

struct Vector;

struct Vector {
        size_t size;      // size of the memory in use
        size_t capacity;  // total capacity of the vector
        int* data;        // data of the vector
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
void vector_resize(struct Vector* vector, size_t new_size, int val);

// gets the size of the vector
size_t vector_size(struct Vector* vector);

// gets the total capacity
size_t vector_capacity(struct Vector* vector);

// appends something to the end of the size of the vector and increases size by
// 1. If the vector is too small, it reallocates it so it is 1.5x the original
// size
void vector_pushback(struct Vector* vector, int val);

// sets a specified inddex to a new elment
// unsafe without bounds checking
void vector_set(struct Vector*, unsigned int index, int val);

// gets a specified inddex to a new elment
// unsafe without bounds checking
int vector_get(struct Vector*, unsigned int index);

// deletes an elment from a vector and shifts all elments to the right of it
// back 1
// unsafe without bounds checking
void vector_remove(struct Vector*, unsigned int index);

// frees the entire vector
void vector_free(struct Vector*);
