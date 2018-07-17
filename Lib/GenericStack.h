#include <stdio.h>
#include <stdlib.h>
#include "Util.h"

/**
 * Macros to create a generic stack (FIFO) data structure
 */

// declares for the functions relating to a stack
// TYPE is the type of data the stack holds
// PREFIX is like the namespace for all functions of that stack
#define STACK_DECLARE(TYPE, PREFIX)                                           \
        /* Types... */                                                        \
        /* --------------------- */                                           \
                                                                              \
        struct PREFIX##_Stack;                                                \
        struct PREFIX##_Stack {                                               \
                size_t size; /* number of elements the stack currently has*/  \
                struct PREFIX##_StackNode* top; /*pointer to the first node*/ \
        };                                                                    \
                                                                              \
        struct PREFIX##_StackNode {                                           \
                TYPE data;                       /*actual data of the node*/  \
                struct PREFIX##_StackNode* next; /*pointer to the next node*/ \
        };                                                                    \
                                                                              \
        /* Procedures... */                                                   \
        /* --------------------- */                                           \
                                                                              \
        /* stack_init */                                                      \
        /* initializes a new stack*/                                          \
        void PREFIX##_stack_init(struct PREFIX##_Stack* stack);               \
                                                                              \
        /* stack_free */                                                      \
        /*frees the space allocated for the stack*/                           \
        void PREFIX##_stack_free(struct PREFIX##_Stack* stack);               \
                                                                              \
        /* stack_size */                                                      \
        /* gets the stack size*/                                              \
        size_t PREFIX##_stack_size(struct PREFIX##_Stack* stack);             \
                                                                              \
        /* stack_peek */                                                      \
        /* gets the top elment of the stack WARNING: does not do bounds       \
         * checking */                                                        \
        TYPE PREFIX##_stack_peek(struct PREFIX##_Stack* stack);               \
                                                                              \
        /* stack_pop */                                                       \
        /* gets the top elment of the stack and removes it from the           \
         * stack. WARNING: does not do bounds checking */                     \
        TYPE PREFIX##_stack_pop(                                              \
            struct PREFIX##_Stack* stack); /* gets the top element of the     \
                                     stack and removes it from the stack */   \
                                                                              \
        /* stack_push */                                                      \
        /* pushes an elment to the top of the stack           */              \
        void PREFIX##_stack_push(                                             \
            struct PREFIX##_Stack* stack,                                     \
            TYPE val); /* pushes an element to the top of the stack*/

// defines the declarations
#define STACK_DEFINE(TYPE, PREFIX)                                             \
                                                                               \
        /* stack_init */                                                       \
        void PREFIX##_stack_init(struct PREFIX##_Stack* stack) {               \
                stack->size = 0;                                               \
                stack->top = NULL;                                             \
        }                                                                      \
                                                                               \
        /* stack_free*/                                                        \
        void PREFIX##_stack_free(struct PREFIX##_Stack* stack) {               \
                struct PREFIX##_StackNode* tmp;                                \
                while ((tmp = stack->top) != NULL) {                           \
                        stack->top = tmp->next;                                \
                        free(tmp);                                             \
                }                                                              \
                free(stack);                                                   \
        }                                                                      \
                                                                               \
        /* stack_free*/                                                        \
        size_t PREFIX##_stack_size(struct PREFIX##_Stack* stack) {             \
                return stack->size;                                            \
        }                                                                      \
                                                                               \
        /* stack_peek*/                                                        \
        TYPE PREFIX##_stack_peek(struct PREFIX##_Stack* stack) {               \
                return stack->top->data;                                       \
        }                                                                      \
                                                                               \
        /* stack_pop */                                                        \
        TYPE PREFIX##_stack_pop(struct PREFIX##_Stack* stack) {                \
                struct PREFIX##_StackNode* tmp = stack->top;                   \
                TYPE val = tmp->data;                                          \
                stack->top = stack->top->next;                                 \
                free(tmp);                                                     \
                --stack->size;                                                 \
                return val;                                                    \
        }                                                                      \
                                                                               \
        /* stack_push */                                                       \
        void PREFIX##_stack_push(struct PREFIX##_Stack* stack, TYPE val) {     \
                struct PREFIX##_StackNode* new_stack_node =                    \
                    (struct PREFIX##_StackNode*)malloc(                        \
                        sizeof(struct PREFIX##_StackNode));                    \
                if (new_stack_node == NULL) {                                  \
                        fprintf(                                               \
                            stderr,                                            \
                            "Major: failed to allocate the new StackNode.\n"); \
                } else {                                                       \
                        new_stack_node->data = val;                            \
                        new_stack_node->next = stack->top;                     \
                        stack->top = new_stack_node;                           \
                        ++stack->size;                                         \
                }                                                              \
        }
