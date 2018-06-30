#include "RunEngine.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

int ECS_runEngine() {
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;
        SDL_Surface *bitmapSurface = NULL;
        SDL_Texture *bitmapTex = NULL;
        int posX = 100, posY = 100, width = 320, height = 240;

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                             "Couldn't initialize SDL: %s", SDL_GetError());
                return 1;
        }

        // clang-format off
        window = SDL_CreateWindow("sdl2 window"
                                 , SDL_WINDOWPOS_UNDEFINED   // x position
                                 , SDL_WINDOWPOS_UNDEFINED   // y position
                                 , 640                       // width
                                 , 480                       // height
                                 , SDL_WINDOW_OPENGL         // flags
                                 );
        // clang-format on

        if (window == NULL) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                             "Window creation failed: %s", SDL_GetError());
                return 1;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                             "Failed to create renderer: %s", SDL_GetError());
                return 1;
        }

        bitmapSurface =
            SDL_LoadBMP("/home/jared/Programs/SpaceGame/Src/Engine/tmp.bmp");
        if (bitmapSurface == NULL) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                             "Failed to load bitmap: %s", SDL_GetError());
                return 1;
        }
        bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
        SDL_FreeSurface(bitmapSurface);

        while (1) {
                SDL_Event e;
                if (SDL_PollEvent(&e)) {
                        if (e.type == SDL_QUIT) {
                                break;
                        }
                }

                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, bitmapTex, NULL, NULL);
                SDL_RenderPresent(renderer);
        }

        SDL_DestroyTexture(bitmapTex);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_Quit();

        return 0;
}
