#include "IDFreeList.h"
#include <stdio.h>
#include "lib/Lists/UIntNodes.h"

// creates a new free list.
struct FreeList createFreeList(size_t free_list_size) {
        // creating the linked list that contains all the empty elements
        struct Node* empty_elements_list = createNode(0, NULL);
        for (size_t i = 1; i < free_list_size; ++i) {
                prepend(i, &empty_elements_list);
        }

        struct FreeList freelist = (struct FreeList){
            .emptyElements = empty_elements_list,
            .sparseArray =
                (struct ID*)malloc(sizeof(struct ID) * free_list_size)};

        if (freelist.sparseArray == NULL) {
                fprintf(stderr, "failed to allocate memory.\n");
        }

        return freelist;
}

// TODO ADD ERROR HANDLING IF THERE IS NO SPACE LEFT IN THE ARRAY
void addToFreeList(struct FreeList* freelist, struct ID id) {
        unsigned int freeindex = popHead(&freelist->emptyElements);
        freelist->sparseArray[freeindex] = id;
}

// TODO ADD ERROR HANDLING IF THERE IT IS OUT OF BOUNDS
void removeFromFreeList(struct FreeList* freelist, unsigned int index) {
        prepend(index, &freelist->emptyElements);
}

void printID(struct ID id) {
        printf("ID: ");
        printf("index %u; ", id.index);
        printf("generation %u", id.generation);
}

void printIDArray(struct ID* id_array, size_t len) {
        for (size_t i = 0; i < len; ++i) {
                printID(id_array[i]);
                printf("\n");
        }
}

void FreeListTestSuit() {
        struct FreeList wuv = createFreeList(10);
        printIDArray(wuv.sparseArray, 10);
        printf("\n");

        addToFreeList(&wuv, (struct ID){3, 2});
        addToFreeList(&wuv, (struct ID){3, 2});
        addToFreeList(&wuv, (struct ID){3, 2});
        addToFreeList(&wuv, (struct ID){3, 2});
        addToFreeList(&wuv, (struct ID){3, 2});
        addToFreeList(&wuv, (struct ID){3, 2});
        addToFreeList(&wuv, (struct ID){3, 2});
        addToFreeList(&wuv, (struct ID){3, 2});
        addToFreeList(&wuv, (struct ID){3, 2});
        addToFreeList(&wuv, (struct ID){3, 2});
        removeFromFreeList(&wuv, 4);
        addToFreeList(&wuv, (struct ID){9, 0});
        printIDArray(wuv.sparseArray, 10);
}
