#include "V2.h"
#include "stdio.h"

__attribute__((pure)) struct V2 V2_add(const struct V2* const a,
                                       const struct V2* const b) {
        return (struct V2){.x = a->x + b->x, .y = a->y + b->y};
}

__attribute__((pure)) struct V2 V2_sub(const struct V2* const a,
                                       const struct V2* const b) {
        return (struct V2){.x = a->x - b->x, .y = a->y - b->y};
}

__attribute__((pure)) struct V2 V2_mul(const struct V2* const a,
                                       const struct V2* const b) {
        return (struct V2){.x = a->x * b->x, .y = a->y * b->y};
}

__attribute__((pure)) struct V2 V2_smul(const struct V2* const a,
                                        const float b) {
        return (struct V2){.x = a->x * b, .y = a->y * b};
}

void V2_print(const struct V2* const val) {
        printf("V2 { .x = %.6f, .y = %.6f }\n", val->x, val->y);
}
