#pragma once

#include "Lib/GenericVector.h"
#include "Lib/sizet_Vector.h"

/** PathFindingNode.h
 * The data type for a node in th epathfinding graph for A* and its associated
 * functions for clean up and initialization.
 */

// -----------------------------------------
//    Types.
// -----------------------------------------

VECTOR_DECLARE(float, Float);

struct PATH_Node {
	size_t parent_node;
	struct SizetVector child_nodes;
	struct FloatVector distance_vector;
};


// -----------------------------------------
//    Procedures
// -----------------------------------------
