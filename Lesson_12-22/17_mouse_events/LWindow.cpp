#include <memory>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LWindow.h"
#include "LTexture.h"
#include "LButton.h"
#include "buttonSprites.h"
#include "colours.h"
#include "customDeleter.h"
#include "globalConstants.h"

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

bool LWindow::loadMedia(LTexture& spriteSheetTexture, std::string& path, std::array<SDL_Rect, LButtonSprite::BUTTON_SPRITE_TOTAL>& spriteClips, std::array<LButton, LButtonSprite::BUTTON_SPRITE_TOTAL>& buttonsArray)
{  
    if (!spriteSheetTexture.loadFromFile(path, *this)) {
        std::cout << "Failed to load sprite sheet texture!\n";
        return false;
    }
    
    for (int i{ 0 }; i < LButtonSprite::BUTTON_SPRITE_TOTAL; ++i) {
        spriteClips[i].x = 0;
        spriteClips[i].y = i * 200;
        spriteClips[i].w = gButtonConstants::BUTTON_WIDTH;
        spriteClips[i].h = gButtonConstants::BUTTON_HEIGHT;    
    }

    buttonsArray[0].setTopLeftPosition(0, 0);
    buttonsArray[1].setTopLeftPosition(SCREEN_WIDTH - gButtonConstants::BUTTON_WIDTH, 0);
    buttonsArray[2].setTopLeftPosition(0, SCREEN_HEIGHT - gButtonConstants::BUTTON_HEIGHT);
    buttonsArray[3].setTopLeftPosition(SCREEN_WIDTH - gButtonConstants::BUTTON_WIDTH, SCREEN_HEIGHT - gButtonConstants::BUTTON_HEIGHT);

    return true;
}