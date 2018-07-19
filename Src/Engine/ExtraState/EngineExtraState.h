#include "Lib/Time.h"
#include "Lib/V2.h"

// The core type that contains "globally" required state
struct ECS_ExtraState;
struct ECS_ExtraState {
        Time dt;                    // time taken to render the frame
        struct V2 camera_position;  // camera position
        // TODO keys / input
};
