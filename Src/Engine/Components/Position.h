#pragma once
#include "Lib/GenericVector.h"

typedef struct Position {
        float x;
        float y;
} Position;

VECTOR_DECLARE(Position, Position)

struct PositionManager;
struct PositionManager {
        struct Position_Vector positions;
};
