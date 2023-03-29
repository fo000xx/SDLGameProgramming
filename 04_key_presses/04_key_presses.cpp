#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <iostream>
#include <memory>
#include <string>

//key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

//custom deleter for the unique pointer
template<typename T>
void custom_delete(T* d) {}

template<typename T>
struct custom_deleter
{
    void operator()(T* d) const
    {
        custom_delete(d);
    }
};

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//window to render to
std::unique_ptr<SDL_Window, custom_deleter<SDL_Window>> gWindow{};

//surface on the window
std::unique_ptr<SDL_Surface, custom_deleter<SDL_Surface>> gScreenSurface{};

//image on the screen
std::unique_ptr<SDL_Surface, custom_deleter<SDL_Surface>> gCurrentSurface{};

//images that correspond to a keypress
std::unique_ptr<SDL_Surface, custom_deleter<SDL_Surface>> gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL]{};

//start SDL and create window
bool init()
{
    //initialisation flag
    bool success = true;

    //initialise SDL
    if(SDL_Init( SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialise! SDL Error: " << SDL_GetError() << '\n';
        success = false;
    }
    else
    {
        //create window
        gWindow.reset(SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
        if(gWindow == NULL)
        {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
            success = false;
        }
        else
        {
            //get window surface
            gScreenSurface.reset(SDL_GetWindowSurface(gWindow.get()));
        }
    }

    return success;
}

//load individual image
std::unique_ptr<SDL_Surface, custom_deleter<SDL_Surface>> loadSurface(std::string path)
{
    //load image at specified path
    std::unique_ptr<SDL_Surface, custom_deleter<SDL_Surface>> loadedSurface{};
    loadedSurface.reset(SDL_LoadBMP(path.c_str()));
    if(loadedSurface == NULL)
    {
        std::cout << "Unable to load image " << path.c_str() << "! SDL Error: " << SDL_GetError() << '\n';
    }

    return loadedSurface;
}

//load media
bool loadMedia()
{
    //loading success flag
    bool success = true;

    //load default surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT].reset(loadSurface("press.bmp").get());
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        std::cout << "Unable to load default image\n";
        success = false;
    }

    //load up surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP].reset(loadSurface("up.bmp").get());
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
    {
        std::cout << "Unable to load up image\n";
        success = false;
    }
    
    //load down surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN].reset(loadSurface("down.bmp").get());
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        std::cout << "Unable to load down image\n";
        success = false;
    }

    //load down surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT].reset(loadSurface("left.bmp").get());
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        std::cout << "Unable to load left image\n";
        success = false;
    }

    //load down surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT].reset(loadSurface("right.bmp").get());
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        std::cout << "Unable to load right image\n";
        success = false;
    }
    return success;
}

//frees media and shuts down SDL
//media is not required to be freed as smart pointers are used
void close()
{
    //quit SDL subsystems
    SDL_Quit();
}

int main()
{
    //start SDL and create window
    if(!init())
    {
        std::cout << "Failed to initialise\n";
    }
    else
    {
        //load media
        if(!loadMedia())
        {
            std::cout << "Failed to load media\n";
        }
        else
        {
            //main loop flag
            bool quit = false;

            //event handler
            SDL_Event e;

            //set default current surface
            gCurrentSurface.reset(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT].get());

            //while applicaiton is running
            while(!quit)
            {
                //handle events on queue
                while(SDL_PollEvent(&e) != 0)
                {
                    //User requests quit
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }

                    //user presses a key
                    else if( e.type == SDL_KEYDOWN)
                    {
                        //select surfaces based on key press
                        switch(e.key.keysym.sym)
                        {
                            case SDLK_UP:
                            gCurrentSurface.reset(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP].get());
                            break;

                            case SDLK_DOWN:
                            gCurrentSurface.reset(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN].get());
                            break;

                            case SDLK_LEFT:
                            gCurrentSurface.reset(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT].get());
                            break;

                            case SDLK_RIGHT:
                            gCurrentSurface.reset(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT].get());
                            break;

                            default:
                            gCurrentSurface.reset(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT].get());
                            break;
                        }
                    }
                }
        
                //apply image
                SDL_BlitSurface(gCurrentSurface.get(), NULL, gScreenSurface.get(), NULL);

                //update the surface
                SDL_UpdateWindowSurface(gWindow.get());
            }
        }
    }
    
    //free resources and close SDL
    close();

    return 0;
}