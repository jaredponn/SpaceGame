#pragma once
#include <stdlib.h>
#include "../Util.h"

/**
 * Declarations for a generic stack (FIFO) data structure
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

#define Stack MACRO_CONCAT(TYPED, _Stack)
#define stack_new MACRO_CONCAT(TYPED, _stack_new)
#define stack_free MACRO_CONCAT(TYPED, _stack_free)
#define stack_size MACRO_CONCAT(TYPED, _stack_size)
#define stack_peek MACRO_CONCAT(TYPED, _stack_peek)
#define stack_pop MACRO_CONCAT(TYPED, _stack_pop)
#define stack_push MACRO_CONCAT(TYPED, _stack_push)

// -----------------------------------------
//    Types
// -----------------------------------------

struct Stack;

// -----------------------------------------
//    Procedures
// -----------------------------------------

// create new stack
struct Stack* stack_new(void);

// free the space allocated for a stack
void stack_free(struct Stack* stack);

// determine the number of elmements in a stack
size_t stack_size(struct Stack* stack);

// returns the top element of a stack
// stack must contain one element.
// Warning: unsafe and does not do bounds checking
GENERICTYPE stack_peek(struct Stack* stack);

// returns the pop elment of a stack and
// removes it from the stack.
// stack must contain one element
// Warning: unsafe and does not do bounds checking
GENERICTYPE stack_pop(struct Stack* stack);

// adds an element to the stack
void stack_push(struct Stack* stack, GENERICTYPE val);

#endif  // TYPED
#endif  // TYPE
