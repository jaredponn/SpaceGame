#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

/**
 * Declarations for functions that load resources (images, window/renderer, and
 * TODO sound)
 */

// -----------------------------------------
//    Procedures for SDL
// -----------------------------------------

// loads the SDL for loading with the given flags
void RSC_initSDL(const Uint32 flags);

// wrapper for SDL_CreateWindow. If create window fails, it will return null and
// print out an error message.
SDL_Window* RSC_createNewWindow(const char* title, int x, int y, int w, int h,
                                Uint32 flags);

// Simliar to RSC_createNewWindow. Intended to be used to create hte initial
// window, as it will call exit(1) if it fails
SDL_Window* RSC_createInitWindow(const char* title, int x, int y, int w, int h,
                                 Uint32 flags);

// wrapper for SDL_CreateRenderer, but assumes that we want the first driver
// that supports the flags provided.
SDL_Renderer* RSC_createNewRenderer(SDL_Window* window, Uint32 flags);

// Simliar to RSC_createNewRenderer. Intended to be used to create hte initial
// window, as it will call exit(1) if it fails
SDL_Renderer* RSC_createInitRenderer(SDL_Window* window, Uint32 flags);

// -----------------------------------------
//    Procedures for SDL_image
// -----------------------------------------

// loads the SDL_image library for loading other image types.
/* Accepts: flags: flags of which images the library should load
 * Returns: Nothing
 * Calls exit(1); if it fails to initialize
 * Example usage: RSC_initSDLImage(IMG_INIT_PNG | IMG_INIT_JPG);
 */
void RSC_initSDLImage(const int flags);

// closes the SDL_image library
// https://www.libsdl.org/projects/SDL_image/docs/SDL_image_9.html#SEC9
void RSC_quitSDLImage();

// loads the image and returns the pointer to the SDL_Texture.
// If it loads unsuccesffully, it will print an error message and return NULL
SDL_Texture* RSC_loadImage(SDL_Renderer* renderer, const char* path);
