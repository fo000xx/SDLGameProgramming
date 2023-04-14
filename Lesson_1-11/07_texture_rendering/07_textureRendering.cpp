#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
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

namespace SCREENPARAMS
{
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//window to render to
std::unique_ptr<SDL_Window, custom_deleter<SDL_Window>> gWindow{};

//window renderer
std::unique_ptr<SDL_Renderer, custom_deleter<SDL_Renderer>> gRenderer{};

//current displayed texture
std::unique_ptr<SDL_Texture, custom_deleter<SDL_Texture>> gTexture{};

//current surface
std::unique_ptr<SDL_Surface, custom_deleter<SDL_Surface>> loadedSurface{};
}

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
        SCREENPARAMS::gWindow.reset(SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENPARAMS::SCREEN_WIDTH, SCREENPARAMS::SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
        if(SCREENPARAMS::gWindow == NULL)
        {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << '\n';
            success = false;
        }
        else 
        {
            //create renderer for the window
            SCREENPARAMS::gRenderer.reset(SDL_CreateRenderer(SCREENPARAMS::gWindow.get(), -1, SDL_RENDERER_ACCELERATED));
            if (SCREENPARAMS::gRenderer == NULL)
            {
                std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << '\n';
                success = false;
            }
            else
            {
                //initialize rendere colour
                SDL_SetRenderDrawColor(SCREENPARAMS::gRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);

                //initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags))
                {
                    std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << '\n';
                    success = false;
                }
            }
        }
    }

    return success;
}

std::unique_ptr<SDL_Texture, custom_deleter<SDL_Texture>> loadTexture(std::string path)
{
    //the final texture
    std::unique_ptr<SDL_Texture, custom_deleter<SDL_Texture>> newTexture{};

    /* //create a temp surface and convert to a texture
    //load image at specified path
    std::unique_ptr<SDL_Surface, custom_deleter<SDL_Surface>> loadedSurface{};
    loadedSurface.reset(IMG_Load(path.c_str()));
    if(loadedSurface == NULL)
    {
        std::cout << "Unable to load image " << path.c_str() << "! SDL Error: " << IMG_GetError() << '\n';
    }
    else 
    {
        //create texture from surface pixels
        newTexture.reset(SDL_CreateTextureFromSurface(SCREENPARAMS::gRenderer.get(), loadedSurface.get()));
        if(newTexture == NULL)
        {
            std::cout << "Unable to create texture from " << path.c_str() << " SDL Error: " << SDL_GetError() << '\n';
        }

        //get rid of old loaded surface
        SDL_FreeSurface(loadedSurface.get());
    }
    */

    //the above section of code is replaced by IMG_LoadTexture as below.
    newTexture.reset(IMG_LoadTexture(SCREENPARAMS::gRenderer.get(), path.c_str()));

    return newTexture;
}

//load media
bool loadMedia()
{
    //loading success flag
    bool success = true;

    //load splash image
    SCREENPARAMS::gTexture.reset(loadTexture("texture.png").get());
    if(SCREENPARAMS::gTexture == NULL)
    {
        std::cout << "Unable to load  texture image ""texture.png"" SDL Error: " << SDL_GetError() << '\n';
        success = false;
    }

    return success;
}

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
                    //if user requests quit
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }

                //clear screen
                SDL_RenderClear(SCREENPARAMS::gRenderer.get());

                //render texture to screen
                SDL_RenderCopy(SCREENPARAMS::gRenderer.get(), SCREENPARAMS::gTexture.get(), NULL, NULL);

                //update screen
                SDL_RenderPresent(SCREENPARAMS::gRenderer.get());
            }
        }
    }
}