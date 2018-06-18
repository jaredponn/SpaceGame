#include "GenericFreeList.h"

// -----------------------------------------
//    Procedures
// -----------------------------------------

void freelist_init(struct FreeList* freelist) {
        struct i_Vector vec;
        i_vector_init(&vec);
        freelist->data = vec;

        struct size_t_Stack stack;
        size_t_stack_init(&stack);
        freelist->free_elements = stack;
}

// wrapper for vector_reserve. Should only be called after inititziatlino
void freelist_reserve(struct FreeList* freelist, size_t new_capacity) {
        i_vector_reserve(&freelist->data, new_capacity);
}

// adds an element to the nearest spot on the structure
void freelist_add(struct FreeList* freelist, int val) {
        // if there are no empty nodes, just push it back on the vector
        if (size_t_stack_size(&freelist->free_elements) == 0) {
                i_vector_pushback(&freelist->data, val);
        }
        // otherwise fill up the node on the stack
        else {
                size_t empty_index = size_t_stack_pop(&freelist->free_elements);
                i_vector_set(&freelist->data, empty_index, val);
        }
}

// gets an element at an index
int freelist_get(struct FreeList* freelist, size_t index) {
        return i_vector_get(&freelist->data, index);
}

// removes an element at the given index. Appends it to the free_elements stack
// NOTE: Does not actually delete the element. It just marks it for writing over
// later
void freelist_removeat(struct FreeList* freelist, size_t index) {
        size_t_stack_push(&freelist->free_elements, index);
}
