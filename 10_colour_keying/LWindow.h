#ifndef LWINDOW_H
#define LWINDOW_H

#include <memory>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <SDL2/SDL_image.h>
#include "colours.h"
#include "customDeleter.h"

class LWindow;
class LTexture;

class LWindow
{
public:
    LWindow()
    {
        //is it bad practice to have multiple try/throws to one catch?
        try {    
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::runtime_error(std::string("SDL could not initialise ") + SDL_GetError());
        }
        } catch (const std::exception& exception) {
            std::cout << "Standard Exception: " << exception.what() << '\n';
        }

        try {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            throw std::runtime_error("Warning: Linear texture filtering not enabled");     
        }
        } catch (const std::exception& exception) {
            std::cout << "Standard Exception: " << exception.what() << '\n';
        }        
        
        mWindow.reset(SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));

        try {
        if (mWindow == NULL) {
            throw std::runtime_error(std::string("Window could not be created! SDL Error: ") + SDL_GetError());        
        }
        } catch (const std::exception& exception) {
            std::cout << "Standard Exception: " << exception.what() << '\n';
        }
        
        mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED));
        
        try {
        if (mRenderer == NULL) {
            throw std::runtime_error(std::string("Renderer could not be created! SDL Error: ") + SDL_GetError());     
        }
        } catch (const std::exception& exception) {
            std::cout << "Standard Exception: " << exception.what() << '\n';
        }
        
        SDL_SetRenderDrawColor(mRenderer.get(), WHITE::red_rgba, WHITE::green_rgba, WHITE::blue_rgba, WHITE::alpha_rgba);
        
        int imgInitFlags = IMG_INIT_PNG;
        
        try {
        if (!(IMG_Init(imgInitFlags) & imgInitFlags)) {
            throw std::runtime_error(std::string("SDL_image could not initialize! SDL_image Error: ") + IMG_GetError());  
        }
        } catch (const std::exception& exception) {
            std::cout << "Standard Exception: " << exception.what() << '\n';
        }        
    }

    bool loadMedia(LTexture& fooTexture, LTexture& backgroundTexture);

    SDL_Renderer& getRenderer(){ return *mRenderer; }
    
private:
    const int SCREEN_WIDTH{ 640 };
    const int SCREEN_HEIGHT{ 480 };
    
    std::unique_ptr<SDL_Window, customDeleter<SDL_Window>> mWindow{};
    std::unique_ptr<SDL_Renderer, customDeleter<SDL_Renderer>> mRenderer{};
};

#endif