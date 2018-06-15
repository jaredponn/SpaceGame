#include "IDFreeList.h"

#include "lib/Lists/UIntNodes.h"

struct FreeList createFreeList(size_t free_list_size) {
        // creating the empty list elements
        struct Node* empty_elements_list = createNode(0, NULL);
        for (size_t i = 1; i < free_list_size; ++i) {
                prepend(i, &empty_elements_list);
        }

        printNodes(empty_elements_list);

        struct FreeList freelist = (struct FreeList){
            .emptyElements = empty_elements_list,
            .sparseArray =
                (struct ID*)malloc(sizeof(struct ID) * free_list_size)};

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
