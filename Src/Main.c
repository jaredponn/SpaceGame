#include "Engine/Engine.h"

#define INITCAPACITY 10000

int main(void) {
        // initializing the libraries
        ECS_initLibraries();

        // initalizing the compoents
        struct ECS_Components engineComponents;
        ECS_initComponents(&engineComponents, INITCAPACITY);

        // loading the resources
        struct ECS_ResourceRegistry resourceRegistry;
        ECS_loadInitResources(&resourceRegistry);

        // declaring/ initlizting the extras
        struct ECS_ExtraState engineExtraState;
        ECS_initExtraState(&engineExtraState);

        struct ECS_EventManager engineEventManager;
        ECS_initEventManager(&engineEventManager, INITCAPACITY);

        // running the game
        ECS_runEngine(&engineComponents, &resourceRegistry, &engineEventManager,
                      &engineExtraState);

        // closing resources
        ECS_destroyRegistry(&resourceRegistry);
        ECS_quitLibraries();

        return 0;
}
