#include <stdio.h>
#include <stdlib.h>

#include "lib/Lists/UIntNodes.h"

struct Node* createNode(unsigned int n, struct Node* node) {
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        if (new_node == NULL) {
                fprintf(stderr, "failed to allocate memory.\n");
        }

        new_node->data = n;
        new_node->next = node;
        return new_node;
}

struct Node* cons(unsigned int n, struct Node* head) {
        struct Node* new_node = createNode(n, head);
        head = new_node;

        return head;
}

unsigned int head(struct Node* list) { return list->data; }

unsigned int popHead(struct Node** list) {
        unsigned int head_data = head(*list);

        struct Node* snd = (*list)->next;
        free(*list);
        *list = snd;

        return head_data;
}

void prepend(unsigned int n, struct Node** head) { *head = cons(n, *head); }

void printNodes(struct Node* node) {
        struct Node tmp = *node;

        while (tmp.next != NULL) {
                printf("%u \n", tmp.data);
                tmp = *tmp.next;
        }
        printf("%u \n", tmp.data);
}
