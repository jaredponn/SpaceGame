#pragma once
#include <stdio.h>
// -----------------------------------------
//    Macros to create strongly typed V2s
// -----------------------------------------

// declares a V2 with name. E.g -> V2_DECLARE(Position) would create a: Position
// with {.x = ?, .y=?} and the associated functions. Useful for strongly typing
// things. Refer to the regular V2 file for function definitions

#define V2_DECLARE(NAME)                                                \
        struct NAME {                                                   \
                float x;                                                \
                float y;                                                \
        };                                                              \
                                                                        \
        struct NAME NAME##_add(const struct NAME* const,                \
                               const struct NAME* const);               \
                                                                        \
        struct NAME NAME##_sub(const struct NAME* const,                \
                               const struct NAME* const);               \
                                                                        \
        struct NAME NAME##_mul(const struct NAME* const,                \
                               const struct NAME* const);               \
                                                                        \
        struct NAME NAME##_smul(const struct NAME* const, const float); \
                                                                        \
        void NAME##_print(const struct NAME* const);

#define V2_DEFINE(NAME)                                                      \
        struct NAME NAME##_add(const struct NAME* const a,                   \
                               const struct NAME* const b) {                 \
                return (struct NAME){.x = a->x + b->x, .y = a->y + b->y};    \
        }                                                                    \
                                                                             \
        struct NAME NAME##_sub(const struct NAME* const a,                   \
                               const struct NAME* const b) {                 \
                return (struct NAME){.x = a->x - b->x, .y = a->y - b->y};    \
        }                                                                    \
                                                                             \
        struct NAME NAME##_mul(const struct NAME* const a,                   \
                               const struct NAME* const b) {                 \
                return (struct NAME){.x = a->x * b->x, .y = a->y * b->y};    \
        }                                                                    \
                                                                             \
        struct NAME NAME##_smul(const struct NAME* const a, const float b) { \
                return (struct NAME){.x = a->x * b, .y = a->y * b};          \
        }                                                                    \
                                                                             \
        void NAME##_print(const struct NAME* const val) {                    \
                printf(#NAME " { .x = %.6f, .y = %.6f }\n", val->x, val->y); \
        }
