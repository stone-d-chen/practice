#include <stdio.h>
#include <stdint.h>
#include "include/SDL.H"
#include <float.h>
typedef uint32_t u32;
typedef float f32;

int main(int ArgCount, char **Args)
{
    bool is_running = false;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        is_running = true;
        printf("running\n");
    }

    u32 Width = 1280;
    u32 Height = 720;
 

    SDL_Window   *window   = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_POPUP_MENU);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture  *texture  = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, Width, Height);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    while(is_running == true)
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch(event.type)
        {
                case SDL_QUIT:
                {
                    is_running = false;
                } break;
                case SDL_KEYDOWN:
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        {
                            is_running = false;
                        }
                    }
                } break;
        }


        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

    }
    return(0);
}