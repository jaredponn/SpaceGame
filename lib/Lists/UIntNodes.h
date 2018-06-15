#pragma once

struct Node {
        unsigned int data;
        struct Node* next;
};

// creates a pointer to a node with "n" data, and a pointer to "node"
struct Node* createNode(unsigned int n, struct Node* node);
// traverses the node list and prints the elments to console
void printNodes(struct Node* node);

/*
   Higher order functions (composed of base functions + more)
   */

// returns the first data element the list holds, and pops the first element of
// the node. Modifies the original list
unsigned int popHead(struct Node** list);

// prepends n to the front list. Modifies the original list
void prepend(unsigned int n, struct Node** head);

/*
   Base functions
   */

// prepends n  to the front of the list, and returns the new list. Does not
// modify the original list
struct Node* cons(unsigned int n, struct Node* head);

// gets the first elment of the list
unsigned int head(struct Node* list);
