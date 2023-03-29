#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <iostream>
#include <memory>

//custom deleter for the unique pointer
template <typename T>
void custom_delete(T* d) {}

template <typename T>
struct custom_deleter
{
    void operator()(T* d) const
    {
        custom_delete(d);
    }
};

//screen dimension constants
constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

//window to render to
std::unique_ptr<SDL_Window, custom_deleter<SDL_Window>> gWindow{};

//surface on the window
std::unique_ptr<SDL_Surface, custom_deleter<SDL_Surface>> gScreenSurface{};

//image on the screen
std::unique_ptr<SDL_Surface, custom_deleter<SDL_Surface>> gXOut{};

//start and create the window
bool init()
{
    //initialisation flag
    bool success = true;

    //initialise SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialise! SDL Error: " << SDL_GetError() << '\n';
        success = false;
    }
    else 
    {
        //create window
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

//load media
bool loadMedia()
{
    //loading success flag
    bool success = true;

    //load splash image
    gXOut.reset(SDL_LoadBMP("x.bmp"));
    if(gXOut == NULL)
    {
        std::cout << "Unable to load image ""x.bmp"" SDL Error: " << SDL_GetError() << '\n';
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
                }
        
            
                //apply image
                SDL_BlitSurface(gXOut.get(), NULL, gScreenSurface.get(), NULL);

                //update the surface
                SDL_UpdateWindowSurface(gWindow.get());
            }
        }
    }
    
    //free resources and close SDL
    close();

    return 0;
}