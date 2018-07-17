#include "Engine/Engine.h"

int main(void) {
        // initializing the third party libraries (SDL)
        ECS_initLibraries();

        // declaring/ initlizting the core
        struct ECS_Core engineCore;
        ECS_initCore(&engineCore);

        // loading the resources
        struct ECS_ResourceRegistry resourceRegistry;
        ECS_loadInitResources(&resourceRegistry);

        // initalizing the engine
        struct ECS_Components engineComponents;
        ECS_initComponents(&engineComponents, 10000);

        // running the game
        ECS_runEngine(&engineCore, &engineComponents, &resourceRegistry);

        // closing resources
        ECS_destroyRegistry(&resourceRegistry);
        ECS_quitLibraries();

        return 0;
}
