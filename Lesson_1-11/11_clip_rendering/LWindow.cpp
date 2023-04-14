#include <memory>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "LWindow.h"
#include "LTexture.h"
#include "SpriteSheetAreas.h"

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

bool LWindow::loadMedia(LTexture& spriteSheetTexture, std::array<SDL_Rect, 4>& spriteClips)
{
    if (!spriteSheetTexture.loadFromFile("dots.png", *this)) {
       std::cout << "Failed to load sprite sheet texture!\n";
       return false;
    }

    spriteClips[TopLeft].x = 0;
    spriteClips[TopLeft].y = 0;
    spriteClips[TopLeft].w = 100;
    spriteClips[TopLeft].h = 100;

    spriteClips[TopRight].x = 100;
    spriteClips[TopRight].y = 0;
    spriteClips[TopRight].w = 100;
    spriteClips[TopRight].h = 100;

    spriteClips[BottomLeft].x = 0;
    spriteClips[BottomLeft].y = 100;
    spriteClips[BottomLeft].w = 100;
    spriteClips[BottomLeft].h = 100;
    
    spriteClips[BottomRight].x = 100;
    spriteClips[BottomRight].y = 100;
    spriteClips[BottomRight].w = 100;
    spriteClips[BottomRight].h = 100;

    return true;
}