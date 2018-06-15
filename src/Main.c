#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "Engine/EngineState.h"
#include "lib/Lists/IDFreeList.h"
#include "lib/Lists/UIntNodes.h"

const static size_t MAX_ENTITIES = 10;

struct Position {
        float x;
        float y;
};

void printID(struct ID id);
void printIDArray(struct ID* id_array, size_t len);
void printPosition(struct Position position);
void printPositions(struct Position* positions, size_t len);

// main entity funtions
int main() {
        struct FreeList wuv = createFreeList(MAX_ENTITIES);
        printIDArray(wuv.sparseArray, MAX_ENTITIES);
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
        printIDArray(wuv.sparseArray, MAX_ENTITIES);
        return 0;
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

void printPosition(struct Position position) {
        printf("Position: ");
        printf("x %f; ", position.x);
        printf("y %f; ", position.y);
}

void printPositions(struct Position* positions, size_t len) {
        printf("Position: ");
        for (size_t i = 0; i < len; ++i) {
                printPosition(positions[i]);
                printf("\n");
        }
}
