#include <memory>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "LWindow.h"
#include "LTexture.h"
#include "colours.h"
#include "customDeleter.h"

LWindow::LWindow()
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
        
        mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
        
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

        try {
        if (TTF_Init() < 0) {
            throw std::runtime_error(std::string("SDL_ttf could not initialise! SDL_ttf Error: ") + TTF_GetError());
        }
        } catch (const std::exception& exception) {
            std::cout << "Standard Exception: " << exception.what() << '\n';
        }
}

bool LWindow::loadMedia(LTexture& texture, std::string& path)
{  
    auto* rawFontTexture = TTF_OpenFont(path.c_str(), 28);
    if (rawFontTexture == NULL) {
        std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << '\n';
    }

    texture.getFont().reset(std::move(rawFontTexture));
    std::unique_ptr<TTF_Font, customDeleter<TTF_Font>> RAIIFontTexture{ rawFontTexture };
    
    SDL_Color textColour = { BLACK::red_rgba, BLACK::green_rgba, BLACK::blue_rgba, BLACK::alpha_rgba };
    if (!texture.loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColour, *this)) {
       std::cout << "Failed to load texture!\n";
       return false;
    }

    return true;
}