#include "Extern/glad/include/glad/glad.h" // this must be the first include to work with GLFW / OpenGL

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

	GLFWwindow *window = LLS_createWindow(500, 500, "fuckall");
	if (!window) {
		printf("\nFAILED;\n");
		exit(EXIT_FAILURE);
	}

	LLS_makeContextCurrent(window);

	LLS_loadGLLoader(); // must b called after make contextcurrent

	LLS_setSwapInterval(1);

	LLS_setKeyboardCallback(window, INP_defaultKeyboardCallback);

	// setting th edefault clear color to black
	LLS_clearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLuint vbo;

	while (!LLS_shouldWindowClose(window)) {
		INP_pollAndUpdateInputBuffer();
		LLS_clear(GL_COLOR_BUFFER_BIT);

		LLS_genBuffers(1, &vbo);


		unsigned int tst = getKeyboardKeyState(GLFW_KEY_A);
		if (tst == INP_PRESS) {
			printf("ifpress\n");
		}

		if (tst == INP_RELEASE) {
			printf("ifrelease\n");
		}


		LLS_swapBuffers(window);
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
