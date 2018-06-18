#include "GenericStack.h"
#include <stdio.h>
#include "../Util.h"

// -----------------------------------------
//    Types
// -----------------------------------------

// stack nodes
struct StackNode {
        GENERICTYPE data;
        struct StackNode* next;
};

// -----------------------------------------
//    Procedures
// -----------------------------------------

// create new stack
struct Stack* stack_new(void) {
        struct Stack* new_stack =
            (struct Stack*)safe_malloc(sizeof(struct Stack));
        new_stack->size = 0;
        new_stack->top = NULL;
        return new_stack;
}

// initializes a newstack
void stack_init(struct Stack* stack) {
        stack->size = 0;
        stack->top = NULL;
}

// free the space allocated for a stack
void stack_free(struct Stack* stack) {
        struct StackNode* tmp;
        while ((tmp = stack->top) != NULL) {
                stack->top = tmp->next;
                free(tmp);
        }
        free(stack);
}

// determine the number of elmements in a stack
size_t stack_size(struct Stack* stack) { return stack->size; }

// returns the top element of a stack
// stack must contain one element.
// Warning: unsafe and does not do bounds checking
GENERICTYPE stack_peek(struct Stack* stack) { return stack->top->data; }

// returns the pop elment of a stack and
// removes it from the stack.
// stack must contain one element
// Warning: unsafe and does not do bounds checking
GENERICTYPE stack_pop(struct Stack* stack) {
        struct StackNode* tmp = stack->top;
        GENERICTYPE val = tmp->data;

        stack->top = stack->top->next;
        free(tmp);

        --stack->size;
        return val;
}

// adds an element to the stack
void stack_push(struct Stack* stack, GENERICTYPE val) {
        struct StackNode* new_stack_node =
            (struct StackNode*)malloc(sizeof(struct StackNode));
        if (new_stack_node == NULL) {
                fprintf(stderr,
                        "Major: failed to allocate the new StackNode.\n");
        } else {
                new_stack_node->data = val;
                new_stack_node->next = stack->top;
                stack->top = new_stack_node;
                ++stack->size;
        }
}
