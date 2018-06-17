#include "GenericVector.h"
#include <stdio.h>

/**
 * Declarations for a vector (a wrapper for a continious memory object). Not C++
 * standard compliant.
 */

// -----------------------------------------
//    Procedures
// -----------------------------------------

// creates a new vector -- deprecated
struct Vector* vector_new(void);

// intializes a new vector
void vector_init(struct Vector* vector) {
        vector->size = 0;
        vector->capacity = 0;
        vector->data = safe_malloc(0);
}

void vector_reserve(struct Vector* vector, size_t new_capacity) {
        GENERICTYPE* new_data = (GENERICTYPE*)realloc(
            vector->data, sizeof(GENERICTYPE) * new_capacity);

        if (new_data == NULL) {
                printf("Error: insufficient memory upon vector reallocation");
                exit(0);
        } else {
                vector->data = new_data;
                new_data = NULL;

                vector->capacity = new_capacity;
        }
}

// resizes vector to the new size (and reallocates) and gives it a default value
void vector_resize(struct Vector* vector, size_t new_size, GENERICTYPE val) {
        vector_reserve(vector, new_size);
        for (size_t i = vector->size; i < vector->capacity; ++i) {
                vector_set(vector, i, val);
        }

        vector->size = new_size;
        vector->capacity = new_size;
}

// gets the size of the vector
size_t vector_size(struct Vector* vector) { return vector->size; }

// gets the total capacity
size_t vector_capacity(struct Vector* vector) { return vector->capacity; }

// appends something to the end of the size of the vector and increases size by
// 1. If the vector is too small, it reallocates it so it is 1.5x the original
// size
void vector_pushback(struct Vector* vector, GENERICTYPE val) {
        if (vector_size(vector) == vector_capacity(vector)) {
                vector_reserve(vector, vector_capacity(vector) * 1.5);
        }
        vector_set(vector, vector_size(vector), val);

        ++vector->size;
}

// sets a specified index to a new elment
// unsafe
void vector_set(struct Vector* vector, unsigned int index, GENERICTYPE val) {
        vector->data[index] = val;
}

// gets a specified inddex to a new elment
// unsafe
int vector_get(struct Vector* vector, unsigned int index) {
        return vector->data[index];
}

// deletes an elment from a vector and shifts all elments to the right of it
// back 1. reduces the size by 1 as well
// unsafe.
void vector_remove(struct Vector* vector, unsigned int index) {
        for (unsigned int i = index; i < vector_size(vector) - 1; ++i) {
                vector_set(vector, i, vector_get(vector, i + 1));
        }
        --vector->size;
}

// frees the entire vector
void vector_free(struct Vector* vector) { free(vector->data); }

// -----------------------------------------
//    Macros
// -----------------------------------------

#undef Vector
#undef vector_new
#undef vector_init
#undef vector_reserve
#undef vector_resize
#undef vector_size
#undef vector_capacity
#undef vector_pushback
#undef vector_set
#undef vector_remove
#undef vector_free

#undef TYPE
#undef TYPED
