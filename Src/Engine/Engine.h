#pragma once

#include "Components/EngineComponents.h"
#include "EventManager/EventManager.h"
#include "ExtraState/EngineExtraState.h"
#include "Resources/LoadResources.h"
#include "Resources/ResourceRegistry.h"

// -----------------------------------------
//    Initilization procedures
// -----------------------------------------

// initializes SDL
void ECS_initLibraries();

// -----------------------------------------
//    Run
// -----------------------------------------

// runs the engine with the resources
void ECS_runEngine(struct ECS_Components*, struct ECS_ResourceRegistry*,
                   struct ECS_EventManager*, struct ECS_ExtraState*);

// -----------------------------------------
//    Destructors
// -----------------------------------------

// TODO
void ECS_freeResources(struct ECS_ResourceRegistry*);

// closes SDL
void ECS_quitLibraries();
