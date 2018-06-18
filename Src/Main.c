#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "Engine/EngineState.h"
#include "Lib/Stack/IntStack.h"

const static size_t MAX_ENTITIES = 10;

struct Position {
        float x;
        float y;
};

struct PackedArray {
        size_t used;
        size_t length;
        void* packedArray;
};

struct PackedArray createPackedArray(size_t size, size_t len);
struct PackedArray createPackedArray(size_t size, size_t len) {
        return (struct PackedArray){.used = 0,
                                    .length = len,
                                    .packedArray = malloc(len * sizeof(size))};
}

void printPosition(struct Position position);
void printPositionPackedArray(struct PackedArray arr);

// main entity funtions
int main() { return 0; }

void printPosition(struct Position position) {
        printf("Position: ");
        printf("x %f; ", position.x);
        printf("y %f; ", position.y);
}

void printPositionPackedArray(struct PackedArray arr) {
        for (size_t i = 0; i < arr.used; ++i) {
                printPosition(*((struct Position*)arr.packedArray +
                                i * sizeof(struct Position)));
                printf("\n");
        }
        printf("%zu many spaces left\n", (arr.length - arr.used));
}
