#pragma once

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

// TODO: automatically set the viewport to the framebuffer size with callbacks
// https://www.glfw.org/docs/latest/group__window.html#ga3203461a5303bf289f2e05f854b2f7cf
// updates the view port with th eframebuffersize
void LLS_updateViewport(GLFWwindow *window);

void LLS_swapBuffers(GLFWwindow *window);
