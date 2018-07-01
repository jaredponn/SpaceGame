#pragma once

#include "Components/Appearance.h"
#include "Components/Entity.h"
#include "Components/Position.h"
#include "Resources/LoadResources.h"
#include "Resources/ResourceRegistry.h"

// -----------------------------------------
//    State
// -----------------------------------------

extern struct ECS_ResourceRegistry RESOURCE_REGISTRY;

// -----------------------------------------
//    Procedures
// -----------------------------------------

// initializes SDL
void ECS_initLibraries();

// loads the resource registry with a renderer, window, and textures
void ECS_loadInitResources(struct ECS_ResourceRegistry*);

// runs the engine with the resources
void ECS_runEngine(struct ECS_ResourceRegistry);

// closes SDL
void ECS_quitLibraries();
