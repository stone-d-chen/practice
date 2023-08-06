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

struct camera
{
    v3f P;
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


    // we need a camera and a film 
    v3f CameraP = {0, -10, 1};
    v3f CameraZ = Normalize(CameraP - v3f{0,0,0});
    v3f Up = {0,0,1}; 
    v3f CameraX = Normalize(Cross(Up, CameraZ));
    v3f CameraY = Normalize(Cross(CameraZ, CameraX));

    f32 FilmWidth = 1.0;
    f32 FilmHeight = 1.0;
    f32 HalfFilmW = 0.5 * FilmWidth;
    f32 HalfFilmH = 0.5 * FilmHeight;
    f32 FilmD = 1.0;

    /*
        THe Film is always represented in Normalized Device coordinates, so it's always referred to in -1, 1
        but we place the film into the world and the films world coordinates are given by the "width", "height" essentially

    */


    while(is_running == true)
    {

        u32 *PixelPointer = Pixels;

        for(u32 Y = 0; Y < Height; ++Y)
        {
            f32 FilmY = -1.0 + 2.0 * ((f32) Y / Height );
            for(u32 X = 0; X < Width; ++X)
            {
                f32 FilmX = -1.0 + 2.0 * ((f32) X / Width );

                v3f RayOrigin = CameraP;
                v3f RayDirection = Normalize(-CameraZ * FilmD             +
                                              CameraX * FilmX * HalfFilmW +
                                              CameraY * FilmY * HalfFilmH  )



                *PixelPointer++ = 0xFF33FF00;
            }
        }


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




        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_UpdateTexture(texture, NULL, Pixels, (int)(Width * sizeof(u32)));
        SDL_RenderCopyEx(renderer, texture, NULL, NULL, 0, NULL, SDL_FLIP_VERTICAL);
        SDL_RenderPresent(renderer);



        SDL_RenderPresent(renderer);

    }
    return(0);
}