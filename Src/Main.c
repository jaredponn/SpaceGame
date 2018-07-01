#include "Engine/RunEngine.h"

int main(void) {
        // initializing the third party libraries (SDL)
        ECS_initLibraries();

        // loading the resources
        struct ECS_ResourceRegistry RESOURCE_REGISTRY;
        ECS_loadInitResources(&RESOURCE_REGISTRY);

        // running the game
        ECS_runEngine(RESOURCE_REGISTRY);

        // closing resources
        ECS_destroyRegistry(&RESOURCE_REGISTRY);
        ECS_quitLibraries();

        return 0;
}
