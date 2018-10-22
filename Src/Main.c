#include "Extern/glad/include/glad/glad.h" // this must be the first include to work with GLFW / OpenGL

#include "Engine/Engine.h"
#include "Engine/LLSystems/LLSystems.h"
#include "Engine/LLSystems/Render.h"

// shouldn't be be in the godly main file
#include "Lib/Logger.h"

#define INITCAPACITY 10000

int main(void)
{
	// initializing the libraries
	/** ECS_initLibraries(); */

	printf("copiled\n\n");

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

	LLS_glfwMakeContextCurrent(window);
	LLS_setDefaultFramebufferSizeCallback(window);

	if (!LLS_gladLoadGLLoader()) // must b called after make contextcurrent
	{
		LOG_TEXT(0, "ERROR LOADING GLAD");
	}

	LLS_glfwSetSwapInterval(1); // rendering plumbing

	LLS_setKeyboardCallback(
		window, INP_defaultKeyboardCallback); // keyboard plumbing


	// RDR_drawTriangle();
	/** RDR_test(); */
	/** unsigned int triangleBuffer = RDR_createTestTrekant(); */

	while (!LLS_glfwShouldWindowClose(window)) {
		INP_pollAndUpdateInputBuffer();

		// setting th edefault clear color to black
		LLS_glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
		LLS_glClear(GL_COLOR_BUFFER_BIT);

		// meh
		// meh


		unsigned int tst = getKeyboardKeyState(GLFW_KEY_A);
		if (tst == INP_PRESS) {
			printf("ifpress\n");
		}

		if (tst == INP_RELEASE) {
			printf("ifrelease\n");
		}


		LLS_glSwapBuffers(window);
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
