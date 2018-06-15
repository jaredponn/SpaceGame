#pragma once
#include <stdlib.h>

struct ID {
        unsigned int index;  // index refers to the index in the packed array
        int generation;  // generation refers to the generation of the current
                         // id
};

struct FreeList {
        struct Node* emptyElements;
        struct ID* sparseArray;
};

// creates the free list of a given size
struct FreeList createFreeList(size_t free_list_size);

// adds an element to any free elment in the free list
// TODO ADD ERROR HANDLING IF THERE IS NO SPACE LEFT IN THE ARRAY
void addToFreeList(struct FreeList* freelist, struct ID id);

// removes an elemtn from the free list
// TODO ADD ERROR HANDLING IF THERE IT IS OUT OF BOUNDS
void removeFromFreeList(struct FreeList* freelist, unsigned int index);

// printing
void printID(struct ID id);
void printIDArray(struct ID* id_array, size_t len);

// TEST SUITE
void FreeListTestSuit();
