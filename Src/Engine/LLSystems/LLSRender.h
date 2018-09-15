#pragma once
#include "Extern/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
/** Render.h
 * functions for rendering / dealing with the viewport
 */

/** Notes on openGL rendering: NDC are from 0 to 1
 * (0,0) -> bottom left corner
 * (1,1) -> upper right corner
 * viewport describes the transform from NDC to window coordinates
 */

// -----------------------------------------
//    functions
// -----------------------------------------

// MUST be called AFTER makeContextcurrent in Window.h
// error handling is tested with if (! {..})) { ERROR HANDLING}
int LLS_loadGLLoader();

// TODO: automatically set the viewport to the framebuffer size with callbacks
// https://www.glfw.org/docs/latest/group__window.html#ga3203461a5303bf289f2e05f854b2f7cf
// updates the view port with th eframebuffersize
void LLS_updateViewport(GLFWwindow *window);


void LLS_swapBuffers(GLFWwindow *window);

// wrapper for glClearColor - fillsthe backgrond color, r, g, b, opacity
void LLS_clearColor(float, float, float, float);

// wrapper for glClear
void LLS_clear(GLbitfield mask);

// wrapper for glGenBuffers
void LLS_genBuffers(GLsizei n, GLuint *buffers);

// wrapper for glBindBuffer
void LLS_bindBuffer(GLenum target, GLuint buffer);

// wrapper for glBufferData
void LLS_bufferData(GLenum target, GLsizeiptr size, const GLvoid *data,
		    GLenum usage);
