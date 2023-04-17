#include <memory>
#include <iostream>
#include <string_view>
#include <SDL2/SDL_image.h>
#include "LWindow.h"
#include "globalConstants.h"
#include "LTexture.h"

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
}

bool LWindow::loadMedia(LTexture& texture, std::string& path, std::array<SDL_Rect, gConstants::WALKING_ANIMATION_FRAMES>& spriteClips)
{
    if (!texture.loadFromFile(path, *this)) {
       std::cout << "Failed to load texture!\n";
       return false;
    }

    spriteClips[FRAME_ONE].x = 0;
    spriteClips[FRAME_ONE].y = 0;
    spriteClips[FRAME_ONE].w = 64;
    spriteClips[FRAME_ONE].h = 205;

    spriteClips[FRAME_TWO].x = 64;
    spriteClips[FRAME_TWO].y = 0;
    spriteClips[FRAME_TWO].w = 64;
    spriteClips[FRAME_TWO].h = 205;

    spriteClips[FRAME_THREE].x = 128;
    spriteClips[FRAME_THREE].y = 0;
    spriteClips[FRAME_THREE].w = 64;
    spriteClips[FRAME_THREE].h = 205;

    spriteClips[FRAME_FOUR].x = 192;
    spriteClips[FRAME_FOUR].y = 0;
    spriteClips[FRAME_FOUR].w = 64;
    spriteClips[FRAME_FOUR].h = 205;

    return true;
}