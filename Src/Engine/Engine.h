#pragma once

#include "Components/EngineComponents.h"
#include "Core/EngineCore.h"
#include "Resources/LoadResources.h"
#include "Resources/ResourceRegistry.h"

// -----------------------------------------
//    Initilization procedures
// -----------------------------------------

// initializes SDL
void ECS_initLibraries();

// initializes the Core with default values of 0
void ECS_initCore(struct ECS_Core*);

// initializes the game engine. The size_t initialize size of the vectors
void ECS_initComponents(struct ECS_Components*, size_t);

// loads the resource registry with a renderer, window, and textures
void ECS_loadInitResources(struct ECS_ResourceRegistry*);

// -----------------------------------------
//    Run
// -----------------------------------------

// runs the engine with the resources
void ECS_runEngine(struct ECS_Core*, struct ECS_Components*,
                   struct ECS_ResourceRegistry*);

// -----------------------------------------
//    Destructors
// -----------------------------------------

// TODO
void ECS_freeComponents(struct ECS_Components*, size_t);

// TODO
void ECS_freeResources(struct ECS_ResourceRegistry*);

// closes SDL
void ECS_quitLibraries();
