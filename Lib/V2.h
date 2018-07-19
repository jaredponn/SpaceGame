#pragma once

struct V2 {
        float x;  // x coordinate
        float y;  // y coordinate
};

// adds two V2s together and returns the result of the vectors
// e.g. (1, 1) + (2, 3) = (3, 4)
__attribute__((pure)) struct V2 V2_add(const struct V2* const,
                                       const struct V2* const);

// multiples two V2s together and returns the result of the vectors
// e.g. (1, 1) * (2, 3) = (2, 3)
__attribute__((pure)) struct V2 V2_mul(const struct V2* const,
                                       const struct V2* const);

// multiples a V2 together and a single value. Scalar multiplication
// e.g. (1, 1) * 2 = (2, 2)
__attribute__((pure)) struct V2 V2_smul(const struct V2* const, const float);

// print V2
void V2_print(const struct V2* const);
