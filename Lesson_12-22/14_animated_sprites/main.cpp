#include <SDL2/SDL_render.h>
#include <iostream>
#include <string>
#include <memory>
#include <array>
#include <SDL2/SDL_image.h>
#include "LWindow.h"
#include "globalConstants.h"
#include "LTexture.h"
#include "colours.h"

int main()
{
    LWindow currentWindow{};

    std::array<SDL_Rect, gConstants::WALKING_ANIMATION_FRAMES> spriteClips; 
    LTexture spriteSheetTexture;
    std::string spriteSheetPath{ "foo.png"};

    if(!currentWindow.loadMedia(spriteSheetTexture, spriteSheetPath, spriteClips)) {
        std::cout << "Failed to load front media, aborting program\n";
        return 1;
    }
    
    bool userRequestsQuit = false;

    SDL_Event eventHandler;

    int currentFrame{ 0 };

    while(!userRequestsQuit) {
        while(SDL_PollEvent(&eventHandler) != 0) {
            if(eventHandler.type == SDL_QUIT) {
                userRequestsQuit = true;
            }
        }

        SDL_SetRenderDrawColor(&currentWindow.getRenderer(), WHITE::red_rgba, WHITE::green_rgba, WHITE::blue_rgba, WHITE::alpha_rgba);
        SDL_RenderClear(&currentWindow.getRenderer());

        SDL_Rect* currentClip =  &spriteClips[currentFrame / 4];
        spriteSheetTexture.renderTexture((currentWindow.getWidth() - currentClip->w) / 2, (currentWindow.getHeight() - currentClip->h) / 2, currentWindow, currentClip);

        //This function updates the screen
        SDL_RenderPresent(&currentWindow.getRenderer());

        ++currentFrame;

        if(currentFrame / 4 >= gConstants::WALKING_ANIMATION_FRAMES) {
            currentFrame = 0;
        }
    }

    IMG_Quit();
    SDL_Quit();

    return 0;
}