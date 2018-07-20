#pragma once

#include "Components/EngineComponents.h"
#include "ExtraState/EngineExtraState.h"
#include "Resources/LoadResources.h"
#include "Resources/ResourceRegistry.h"

// -----------------------------------------
//    Initilization procedures
// -----------------------------------------

// initializes SDL
void ECS_initLibraries();

// loads the resource registry with a renderer, window, and textures
void ECS_loadInitResources(struct ECS_ResourceRegistry*);

// initializes the extras with default values
void ECS_initExtraState(struct ECS_ExtraState*);

// -----------------------------------------
//    Run
// -----------------------------------------

// runs the engine with the resources
void ECS_runEngine(struct ECS_Components*, struct ECS_ResourceRegistry*,
                   struct ECS_ExtraState*);

// -----------------------------------------
//    Destructors
// -----------------------------------------

// TODO
void ECS_freeResources(struct ECS_ResourceRegistry*);

// closes SDL
void ECS_quitLibraries();
