#include <stdio.h>
#include <stdint.h>
#include "include/SDL.H"
#include <float.h>
typedef uint32_t u32;
typedef float f32;


#include "math.h"

#define ArrayCount(arr) (( sizeof(arr) ) / ( sizeof(*arr) ))

struct sphere
{
    v3f P;
    f32 r;
    u32 MatIdx;
};

struct plane
{
    v3f N;
    f32 d;
    u32 MatIdx;
};

struct material
{
    v3f Color;
};

struct world
{
    u32 MaterialCount;
    material *Materials;

    u32 SphereCount;
    sphere *Spheres;

    u32 PlaneCount;
    plane *Planes;
};






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




    u32 *Pixels = (u32 *) malloc(Width * Height * sizeof(u32));
    
    sphere Spheres[] =  
    {
        { {0,0,0}, 1.0 }
    };
    plane Planes[] =  
    {
        { {0,0,1}, 1}
    };

    material Materials[]
    {
        {0.3, 0.4, 0.5},
        {0.8, 0.5, 0.1},
        {0.0, 0.5, 0.1},
    };

    world World = {};

    World.Spheres = Spheres;
    World.SphereCount = ArrayCount(Spheres);

    World.Planes = Planes;
    World.PlaneCount = ArrayCount(Planes);

    World.Materials = Materials;
    World.MaterialCount = ArrayCount(Materials); 







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


        u32 *PixelPointer = Pixels;
        for(u32 Row = 0; Row < Height; ++Row)
        {
            for(u32 Col = 0; Col < Width; ++Col)
            {
                *PixelPointer++ = 0xFF33FF00;
            }
        }


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_UpdateTexture(texture, NULL, Pixels, (int)(Width * sizeof(u32)));
        SDL_RenderCopyEx(renderer, texture, NULL, NULL, 0, NULL, SDL_FLIP_VERTICAL);
        SDL_RenderPresent(renderer);



        SDL_RenderPresent(renderer);

    }
    return(0);
}