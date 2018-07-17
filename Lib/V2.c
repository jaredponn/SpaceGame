#include "V2.h"

__attribute__((pure)) struct V2 V2_add(const struct V2* const a,
                                       const struct V2* const b) {
        return (struct V2){.x = a->x + b->x, .y = a->y + b->y};
}

__attribute__((pure)) struct V2 V2_mul(const struct V2* const a,
                                       const struct V2* const b) {
        return (struct V2){.x = a->x * b->x, .y = a->y * b->y};
}

__attribute__((pure)) struct V2 V2_smul(const struct V2* const a,
                                        const float b) {
        return (struct V2){.x = a->x * b, .y = a->y * b};
}
