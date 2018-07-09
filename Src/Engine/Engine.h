#pragma once

#include "Components/EngineComponents.h"
#include "Resources/LoadResources.h"
#include "Resources/ResourceRegistry.h"

// -----------------------------------------
//    Procedures
// -----------------------------------------

// initializes SDL
void ECS_initLibraries();

// initializes the game engine. The size_t initialize size of the vectors
void ECS_initComponents(struct ECS_Components*, size_t);

// loads the resource registry with a renderer, window, and textures
void ECS_loadInitResources(struct ECS_ResourceRegistry*);

// runs the engine with the resources
void ECS_runEngine(struct ECS_Components*, struct ECS_ResourceRegistry*);

// TODO
void ECS_freeEngine(struct ECS_Components*, size_t);

// TODO
void ECS_freeResources(struct ECS_ResourceRegistry*);

// closes SDL
void ECS_quitLibraries();
