#include <memory>
#include <iostream>
#include <SDL2/SDL_image.h>

#include "LWindow.h"
#include "LTexture.h"

bool LWindow::loadMedia(LTexture& fooTexture, LTexture& backgroundTexture, LWindow& currentWindow)
{
    //loading success flag
    bool success { true };

    //load Foo' texture
    if (!fooTexture.loadFromFile("foo.png", currentWindow)) {
       std::cout << "Failed to load Foo' texture image!\n";
       success = false; 
    }

    //load background texture
    if (!backgroundTexture.loadFromFile("background.png", currentWindow)) {
        std::cout << "Failed ot load background texture image!\n";
        success = false;
    }

    return success;
}

bool LWindow::init()
{
    //initialisation flag
    bool success { true };

    //initialise SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialise! SDL Error: " << SDL_GetError() << '\n';
        success = false;
    }
    else
    {
        //Create window
        m_Window.reset(SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
        if(m_Window == NULL)
        {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << '\n';
            success = false;
        }
        else 
        {
            //create renderer for the window
            m_Renderer.reset(SDL_CreateRenderer(m_Window.get(), -1, SDL_RENDERER_ACCELERATED));
            if (m_Renderer == NULL)
            {
                std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << '\n';
                success = false;
            }
            else
            {
                //initialize renderer colour
                SDL_SetRenderDrawColor(m_Renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }

    return success;
}

void LWindow::close(LTexture& backgroundTexture, LTexture& fooTexture)
{
    //free loaded images
    fooTexture.free();
    backgroundTexture.free();
    
    //quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}