#include "Engine/Engine.h"
#include "Engine/LLSystems/LLSystems.h"

#define INITCAPACITY 10000

int main(void)
{
	// initializing the libraries
	/** ECS_initLibraries(); */

	printf("copiled");

	LLS_setDefaultErrorCallback();

	if (!LLS_initGraphicsLibFrameWork()) {
		printf("\nFAILED;\n");
		exit(EXIT_FAILURE);
	}

	GLFWwindow *window = LLS_createWindow(100, 100, "fuckall");
	if (!window) {
		printf("\nFAILED;\n");
		exit(EXIT_FAILURE);
	}

	LLS_makeContextCurrent(window);
	LLS_setSwapInterval(1);

	LLS_setKeyboardCallback(window, INP_defaultKeyCallback);

	while (!LLS_shouldWindowClose(window)) {
		LLS_pollEvents();
	}

	LLS_terminateGraphicsLibFrameWork();

	/** // initalizing the compoents sets */
	/** struct CPT_Components engineComponents; */
	/** CPT_initComponents(&engineComponents, INITCAPACITY); */
	/**  */
	/** // loading the resources */
	/** struct RSC_ResourceRegistry resourceRegistry; */
	/** RSC_loadInitResources(&resourceRegistry); */
	/**  */
	/** struct INP_InputMap inputMap; */
	/** ECS_initInput(&inputMap); */
	/**  */
	/** // declaring/ initlizting the extras */
	/** struct EXS_ExtraState engineExtraState; */
	/** ECS_initExtraState(&engineExtraState); */
	/**  */
	/** // running the game */
	/** ECS_runEngine(&engineComponents, &resourceRegistry, &inputMap, */
	/**               &engineExtraState); */
	/**  */
	/** // closing resources */
	/** RSC_destroyRegistry(&resourceRegistry); */
	/** ECS_quitLibraries(); */
	/**  */

	return 0;
}
