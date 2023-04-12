#ifndef LWINDOW_H
#define LWINDOW_H

#include <SDL2/SDL_render.h>
#include <memory>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "colours.h"
#include "customDeleter.h"

class LWindow;
class LTexture;

class LWindow
{
public:
    //if construction fails, clean-up won't be completed. Put the potential failures inside member classes?
    LWindow()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << "SDL could not initialise! SDL Error: " << SDL_GetError() << '\n';
            //abort construction here
        }

        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            std::cout << "Warning: Linear texture filtering not enabled!\n";        
        }
        
        mWindow.reset(SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
        if (mWindow == NULL) {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << '\n';
            //abort construction here        
        }

        mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED));
        if (mRenderer == NULL) {
            std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << '\n';
            //abort construction here        
        }

        SDL_SetRenderDrawColor(mRenderer.get(), White::red_rgba, White::green_rgba, White::blue_rgba, White::alpha_rgba);
        
        //relabel to be clearer //initalize PNG loading.
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << '\n';
        }
    }

    ~LWindow()
    {
        IMG_Quit();
        SDL_Quit();
    }

    bool loadMedia(LTexture& fooTexture, LTexture& backgroundTexture);

    SDL_Renderer& getRenderer(){ return *mRenderer; }
    
private:
    //screen dimension constants
    const int SCREEN_WIDTH{ 640 };
    const int SCREEN_HEIGHT{ 480 };
    
    //window to render to
    std::unique_ptr<SDL_Window, customDeleter<SDL_Window>> mWindow{};

    //window renderer
    std::unique_ptr<SDL_Renderer, customDeleter<SDL_Renderer>> mRenderer{};
};

#endif