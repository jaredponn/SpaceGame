#include "Engine/Engine.h"

#define INITCAPACITY 10000

int main(void)
{
	// initializing the libraries
	ECS_initLibraries();

	// initalizing the compoents sets
	struct CPT_Components engineComponents;
	CPT_initComponents(&engineComponents, INITCAPACITY);

	// loading the resources
	struct RSC_ResourceRegistry resourceRegistry;
	RSC_loadInitResources(&resourceRegistry);

	struct INP_InputMap inputMap;
	ECS_initInput(&inputMap);

	// declaring/ initlizting the extras
	struct EXS_ExtraState engineExtraState;
	ECS_initExtraState(&engineExtraState);

	struct EventManager engineEventManager;
	EventManager_init(&engineEventManager);
	EventManager_reserve(&engineEventManager, INITCAPACITY);

	// running the game
	ECS_runEngine(&engineComponents, &resourceRegistry, &inputMap,
		      &engineEventManager, &engineExtraState);

	// closing resources
	RSC_destroyRegistry(&resourceRegistry);
	ECS_quitLibraries();


	return 0;
}
