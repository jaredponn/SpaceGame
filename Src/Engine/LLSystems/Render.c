#include "Render.h"
#include "Shaders.h"
#include <stdio.h>
// https://open.gl/drawing

// https://www.opengl.org/discussion_boards/showthread.php/170211-VBO-VAO

// http://www.songho.ca/opengl/gl_vbo.html // HONESTLY THE BEST RESOURCE FOR
// UDNERSTANINDG THIS

// https://gamedev.stackexchange.com/questions/99236/what-state-is-stored-in-an-opengl-vertex-array-object-vao-and-how-do-i-use-the

// https://paroj.github.io/gltut/Positioning/Tutorial%2005.html mentions how
// vertexArrays and buffer arrays interactwith eachother

// https://gamedev.stackexchange.com/questions/90471/should-unbind-buffers
// vaovbo order

// https://alfonse.bitbucket.io/oldtut/Basics/Tut01%20Following%20the%20Data.html
// really useful for writing your own entire pipeline

float testTriangle[] = {
	0.0f,  0.5f,  // Vertex 1 (X, Y)
	0.5f,  -0.5f, // Vertex 2 (X, Y)
	-0.5f, -0.5f  // Vertex 3 (X, Y)
};


unsigned int RDR_drawTriangle()
{

	/** creating and compiling the shaders... */
	unsigned int vertexShader =
		LLS_safeCreateAndCompileVertexShader(DEFAULT_VERTEX_SHADER);
	unsigned int fragmentShader =
		LLS_safeCreateAndCompileFragmentShader(WHITE_FRAGMENT_SHADER);


	/** assembling the shader program */
	unsigned int shaderProgram = LLS_glCreateProgram();
	LLS_glAttachShader(shaderProgram, vertexShader);
	LLS_glAttachShader(shaderProgram, fragmentShader);
	LLS_glBindFragDataLocation(shaderProgram, 0, "outColor");

	LLS_glLinkProgram(shaderProgram);

	/** testing if the program is linked TODO move this somewhere else*/
	GLint isLinked = 0;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE) {
		printf("well fuck all");
		fflush(stdout);
	}
	/**  end of the stuff that should be somehwer else */

	LLS_glUseProgram(shaderProgram);

	/** vertex array objects  */
	GLuint vao;
	LLS_glGenVertexArrays(1, &vao);
	LLS_glBindVertexArray(vao);

	/** vbo */
	GLuint vbo;
	LLS_glGenBuffers(1, &vbo);
	LLS_glBindBuffer(GL_ARRAY_BUFFER, vbo);
	LLS_glBufferData(GL_ARRAY_BUFFER, sizeof(testTriangle), testTriangle,
			 GL_STATIC_DRAW);


	GLint posAttrib = LLS_glGetAttribLocation(shaderProgram, "position");
	LLS_glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	LLS_glEnableVertexAttribArray(posAttrib);

	return 0;
}

static const GLfloat testVerticies[] = {
	-1.0f, -1.0f, //
	1.0f,  -1.0f, //
	0.0f,  0.0f   //
};

static GLfloat testColors[3] = {0.5f, 0.5f, 0.5f};

void RDR_oldtest()
{
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, testVerticies);
	glColor3fv(testColors);

	glDisableClientState(GL_VERTEX_ARRAY);
}

unsigned int RDR_createTestTrekant()
{
	// shaders
	/** unsigned int vertexShader = */
	/**         LLS_safeCreateAndCompileVertexShader(DEFAULT_VERTEX_SHADER);
	 */
	/** unsigned int fragmentShader = */
	/**         LLS_safeCreateAndCompileVertexShader(WHITE_FRAGMENT_SHADER);
	 */
	/** unsigned int shaderProgram = LLS_safeLinkVertexAndFragmentShader( */
	/**         vertexShader, fragmentShader); */
	/** LLS_glDeleteShader(vertexShader); */
	/** LLS_glDeleteShader(fragmentShader); */

	GLuint vaoID;
	LLS_glGenVertexArrays(1, &vaoID);
	LLS_glBindVertexArray(vaoID);

	GLuint vboID;
	LLS_glGenBuffers(1, &vboID);		  // generate the id for 1 bufer
	LLS_glBindBuffer(GL_ARRAY_BUFFER, vboID); // initalizse function
	LLS_glBufferData(GL_ARRAY_BUFFER, sizeof(testVerticies), testVerticies,
			 GL_STREAM_DRAW); // copies the data in

	LLS_glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

	LLS_glEnableVertexAttribArray(0);


	/** LLS_glDeleteBuffers(1, &vboID); // frees the buffer */
	return vboID;
}

void RDR_genAndinitTrekantVertexBuffer(unsigned int *vbo)
{
	/** Creates the data and fills it with random binary data */
	// generating the buffer
	LLS_glGenBuffers(1, vbo);

	//  binding (initalizing) the buffer to the context
	LLS_glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	// copying the data over
	LLS_glBufferData(GL_ARRAY_BUFFER, sizeof(testTriangle), testTriangle,
			 GL_STATIC_DRAW);

	LLS_glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinds the buffer

	/** tells OpenGL that there is avertex data in this buffer object, and
	 * what form the vertex data takes  */
	LLS_glBindBuffer(GL_ARRAY_BUFFER, *vbo); // says we're using this buffer
	LLS_glEnableVertexAttribArray(0);
	LLS_glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0,
				  0); // tells how to interpret the buffer info
}
