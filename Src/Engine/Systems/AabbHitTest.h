#pragma once

#include "Src/Engine/Components/Components.h"
#include "../Events/SystemEvents.h"

// -----------------------------------------
//    Tests if the rectangles from the component mangers are colliding. if they
//    are, it will send the event to the event manager
// -----------------------------------------

// tests if there is a hittest between these two hit test layers, and sends an
// event to the event maanger if it sthe case. Please dont send anything other
// than a rectangle manager through these or else weird undefined behavour wil
// occur
void SYS_rectAabbHitTest(const struct RectAabbManager *,
			 const struct RectAabbManager *,
			 struct EVT_SystemEventManager *);

void SYS_circAabbHitTest(const struct CircAabbManager *,
			 const struct CircAabbManager *,
			 struct EVT_SystemEventManager *);

void SYS_circRectAabbHitTest(const struct CircAabbManager *,
			     const struct RectAabbManager *,
			     struct EVT_SystemEventManager *);
