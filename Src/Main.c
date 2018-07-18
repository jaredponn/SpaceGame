#include "Engine/Engine.h"

int main(void) {
        // initializing the third party libraries (SDL)
        ECS_initLibraries();

        // initalizing the engine
        struct ECS_Components engineComponents;
        ECS_initComponents(&engineComponents, 10000);

        // loading the resources
        struct ECS_ResourceRegistry resourceRegistry;
        ECS_loadInitResources(&resourceRegistry);

        // declaring/ initlizting the extras
        struct ECS_Extras engineExtras;
        ECS_initExtras(&engineExtras);

        // running the game
        ECS_runEngine(&engineComponents, &resourceRegistry, &engineExtras);

        // closing resources
        ECS_destroyRegistry(&resourceRegistry);
        ECS_quitLibraries();

        return 0;
}
