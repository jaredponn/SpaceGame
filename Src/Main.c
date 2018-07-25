#include "Engine/Engine.h"

#define INITCAPACITY 10000

int main(void) {
        // initializing the libraries
        ECS_initLibraries();

        // initalizing the compoents sets
        struct CPT_Set engineComponentSet[NUM_OF_COMPONENT_SETS];
        for (size_t i = 0; i < NUM_OF_COMPONENT_SETS; ++i) {
                CPT_initComponents(&engineComponentSet[i], INITCAPACITY);
        }

        // loading the resources
        struct ECS_ResourceRegistry resourceRegistry;
        ECS_loadInitResources(&resourceRegistry);

        struct INP_InputMap inputMap;
        ECS_initInput(&inputMap);

        // declaring/ initlizting the extras
        struct ECS_ExtraState engineExtraState;
        ECS_initExtraState(&engineExtraState);

        struct EventManager engineEventManager;
        EventManager_init(&engineEventManager);
        EventManager_reserve(&engineEventManager, INITCAPACITY);

        // running the game
        ECS_runEngine(engineComponentSet, &resourceRegistry, &inputMap,
                      &engineEventManager, &engineExtraState);

        // closing resources
        ECS_destroyRegistry(&resourceRegistry);
        ECS_quitLibraries();

        return 0;
}
