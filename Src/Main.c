#include "Engine/Engine.h"

int main(void) {
        // initializing the third party libraries (SDL)
        ECS_initLibraries();

        // loading the resources
        struct ECS_ResourceRegistry RESOURCE_REGISTRY;
        ECS_loadInitResources(&RESOURCE_REGISTRY);

        // initalizing the engine
        struct ECS_Components COMPONENTS;
        ECS_initComponents(&COMPONENTS, 10000);

        // running the game
        ECS_runEngine(&COMPONENTS, &RESOURCE_REGISTRY);

        // closing resources
        ECS_destroyRegistry(&RESOURCE_REGISTRY);
        ECS_quitLibraries();

        return 0;
}
