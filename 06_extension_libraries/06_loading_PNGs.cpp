#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <memory>

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

//start SDL and create window
bool init()
{
    //initialisation flag
    bool success = true;

    //initialise SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialise! SDL Error: " << SDL_GetError() << '\n';
        success = false;
    }
    else
    {
        //Create window
        gWindow.reset(SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
        if(gWindow == NULL)
        {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << '\n';
            success = false;
        }
        else 
        {
            //Intialise PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) 
            {
                std::cout << "SDL_image could not initialise! SDL_image Error: " << IMG_GetError() << '\n';
                success = false;
            }
            else
            {
                //get window surface
                gScreenSurface.reset(SDL_GetWindowSurface(gWindow.get()));
            }
        }
    }

    return success;
}

//load individual image
std::unique_ptr<SDL_Surface, custom_deleter<SDL_Surface>> loadSurface(std::string path)
{
    //the final optimized image
    std::unique_ptr<SDL_Surface, custom_deleter<SDL_Surface>> optimizedSurface{};
    
    //load image at specified path
    std::unique_ptr<SDL_Surface, custom_deleter<SDL_Surface>> loadedSurface{};
    loadedSurface.reset(IMG_Load(path.c_str()));
    if(loadedSurface == NULL)
    {
        std::cout << "Unable to load image " << path.c_str() << "! SDL Error: " << IMG_GetError() << '\n';
    }
    else
    {
        //convert surface to screen format
        optimizedSurface.reset(SDL_ConvertSurface(loadedSurface.get(), gScreenSurface->format, 0));
        if(optimizedSurface == NULL)
        {
            std::cout << "Unable to optimize image " << path.c_str() << "! SDL Error: " << SDL_GetError() << '\n';
        }

        //get rid of old loaded surface
        SDL_FreeSurface(loadedSurface.get());
    }

    return optimizedSurface;
}

//load media
bool loadMedia()
{
    //loading success flag
    bool success = true;

    //load splash image
    gCurrentSurface.reset(loadSurface("loaded.png").get());
    if(gCurrentSurface == NULL)
    {
        std::cout << "Unable to load image ""loaded.bmp"" SDL Error: " << SDL_GetError() << '\n';
        success = false;
    }

    return success;
}

//frees media and shuts down SDL
//media is not required to be freed as smart pointers are used
void close()
{
    //quit SDL subsystems
    IMG_Quit();
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
        
                //Apply the image
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