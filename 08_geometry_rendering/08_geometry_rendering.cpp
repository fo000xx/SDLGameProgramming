#include <SDL2/SDL.h>
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
                //initialize renderer colour
                SDL_SetRenderDrawColor(SCREENPARAMS::gRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }

    return success;
}

//load media - essentially redundant at this point
bool loadMedia()
{
    //loading success flag
    bool success = true;

    return success;
}

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
                    //if user requests quit
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }

                //clear screen
                SDL_SetRenderDrawColor(SCREENPARAMS::gRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(SCREENPARAMS::gRenderer.get());

                //render red filled quad
                SDL_Rect fillRect = {SCREENPARAMS::SCREEN_WIDTH / 4, SCREENPARAMS::SCREEN_HEIGHT / 4, SCREENPARAMS::SCREEN_WIDTH / 2, SCREENPARAMS::SCREEN_HEIGHT / 2};
                SDL_SetRenderDrawColor(SCREENPARAMS::gRenderer.get(), 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderFillRect(SCREENPARAMS::gRenderer.get(), &fillRect);

                //render green outlined quad
                SDL_Rect outlineRect = {SCREENPARAMS::SCREEN_WIDTH / 6, SCREENPARAMS::SCREEN_HEIGHT / 6, SCREENPARAMS::SCREEN_WIDTH * 2/3, SCREENPARAMS::SCREEN_HEIGHT * 2/3};
                SDL_SetRenderDrawColor(SCREENPARAMS::gRenderer.get(), 0x00, 0xFF, 0x00, 0xFF);
                SDL_RenderDrawRect(SCREENPARAMS::gRenderer.get(), &outlineRect);

                //draw blue horizontal line
                SDL_SetRenderDrawColor(SCREENPARAMS::gRenderer.get(), 0x00, 0x00, 0xFF, 0xFF);
                SDL_RenderDrawLine(SCREENPARAMS::gRenderer.get(), 0, SCREENPARAMS::SCREEN_HEIGHT / 2, SCREENPARAMS::SCREEN_WIDTH, SCREENPARAMS::SCREEN_HEIGHT / 2);

                //draw vertical line of yellow dots
                SDL_SetRenderDrawColor(SCREENPARAMS::gRenderer.get(), 0xFF, 0xFF, 0x00, 0xFF);
                for(int i = 0; i < SCREENPARAMS::SCREEN_HEIGHT; i += 4)
                {
                    SDL_RenderDrawPoint(SCREENPARAMS::gRenderer.get(), SCREENPARAMS::SCREEN_WIDTH / 2, i);
                }

                //update screen
                SDL_RenderPresent(SCREENPARAMS::gRenderer.get());
            }
        }
    }
}