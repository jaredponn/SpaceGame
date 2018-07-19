#include "Lib/V2.h"
#include "Time.h"

// The core type that contains "globally" required state
struct ECS_Extras;
struct ECS_Extras {
        Time dt;                    // time taken to render the frame
        struct V2 camera_position;  // camera position
        // TODO keys / input
};