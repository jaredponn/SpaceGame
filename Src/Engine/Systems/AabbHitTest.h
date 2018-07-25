#pragma once

#include "Src/Engine/Components/Components.h"
#include "Src/Engine/EventManager/EventManager.h"

// -----------------------------------------
//    Tests if the rectangles from the component mangers are colliding. if they
//    are, it will send the event to the event manager
// -----------------------------------------

void SYS_rectAabbHitTest();
