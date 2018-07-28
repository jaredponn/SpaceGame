#include "LoadResources.h"
#include "Lib/Util.h"
// link for how to do descent RAII in c:
// https://stackoverflow.com/questions/245742/examples-of-good-gotos-in-c-or-c

// -----------------------------------------
//    Procedures for SDL
// -----------------------------------------

// error handler for SDL errors
static void RSC_SDLErrorHandler(const char *msg);

void RSC_initSDL(const Uint32 flags)
{
	if (SDL_Init(flags) != 0) {
		RSC_SDLErrorHandler("Failed to initialize SDL");
		exit(1);
	}
}

SDL_Window *RSC_createInitWindow(const char *title, int x, int y, int w, int h,
				 Uint32 flags)
{
	SDL_Window *window;

	window = RSC_createNewWindow(title, x, y, w, h, flags);

	if (window == NULL) {
		exit(1);
	} else {
		return window;
	}
}

SDL_Window *RSC_createNewWindow(const char *title, int x, int y, int w, int h,
				Uint32 flags)
{
	SDL_Window *window;
	window = SDL_CreateWindow(title, x, y, w, h, flags);

	if (window == NULL) {
		RSC_SDLErrorHandler("Failed to load window. ");
		return NULL;
	}

	return window;
}

SDL_Renderer *RSC_createNewRenderer(SDL_Window *window, Uint32 flags)
{
	SDL_Renderer *renderer;
	renderer = SDL_CreateRenderer(window, -1, flags);

	if (renderer == NULL) {
		RSC_SDLErrorHandler("Failed to create renderer");
		return NULL;
	}

	return renderer;
}

SDL_Renderer *RSC_createInitRenderer(SDL_Window *window, Uint32 flags)
{
	SDL_Renderer *renderer;

	renderer = RSC_createNewRenderer(window, flags);

	if (renderer == NULL)
		exit(1);
	else
		return renderer;
}

static void RSC_SDLErrorHandler(const char *msg)
{
	fprintf(stderr, "%s\n SDL_Image error: %s\n", msg, SDL_GetError());
}

// -----------------------------------------
//    Procedures for SDL_image
// -----------------------------------------

// handles errors for SDL_image. Prints the desired error msg, with the
// SDL_image error message that follows.
static void RSC_SDLIImageErrorHandler(const char *msg);

void RSC_initSDLImage(const int flags)
{
	if (IMG_Init(flags) != flags) {
		RSC_SDLIImageErrorHandler("SDL_image could not initialize! ");
		exit(1);
	}
}

void RSC_quitSDLImage()
{
	IMG_Quit();
}

SDL_Texture *RSC_loadImage(SDL_Renderer *renderer, const char *path)
{
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;

	{
		char *surfaceErrMsg =
			UTI_strcat("Error loading surface at: ", path);

		// loading the image as a surface
		surface = IMG_Load(path);

		// error handling
		if (surface == NULL) {
			RSC_SDLIImageErrorHandler(surfaceErrMsg);
			surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);

			// maybe add more proper error handling for SDL_FillRect
			SDL_FillRect(surface, NULL,
				     SDL_MapRGB(surface->format, 255, 0, 0));

			RSC_SDLIImageErrorHandler(
				"Failed to load image, so loading a red rectangle "
				"instead");
		}

		free(surfaceErrMsg);
	}

	{
		// texture error message
		char *textureErrMsg =
			UTI_strcat("Error loading texture at: ", path);

		// loading the surface
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		// error handling
		if (texture == NULL) {
			RSC_SDLIImageErrorHandler(textureErrMsg);
			return NULL;
		}

		free(textureErrMsg);
	}

	SDL_FreeSurface(surface);

	return texture;
}

static void RSC_SDLIImageErrorHandler(const char *msg)
{
	fprintf(stderr, "%s\n SDL_Image error: %s\n", msg, IMG_GetError());
}
