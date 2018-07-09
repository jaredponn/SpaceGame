#pragma once
#include "Lib/GenericComponentManager.h"
#include "Lib/GenericVector.h"

typedef struct Position {
        float x;  // x coordinate
        float y;  // y coordinate
} Position;

VECTOR_DECLARE(Position, Position)
COMPONENT_MANAGER_DECLARE(Position, Position)
