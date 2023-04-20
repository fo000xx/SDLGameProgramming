#include <iostream>
#include <string>
#include <memory>
#include <array>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LWindow.h"
#include "LTexture.h"
#include "LButton.h"
#include "buttonSprites.h"
#include "colours.h"
#include "globalConstants.h"

int main()
{
    LWindow currentWindow{};

    std::array<LButton, LButtonSprite::BUTTON_SPRITE_TOTAL> buttonsArray;
    std::array<SDL_Rect, LButtonSprite::BUTTON_SPRITE_TOTAL> spriteClips;
    
    LTexture buttonTexture;
    std::string pngPath{ "button.png"};

    if(!currentWindow.loadMedia(buttonTexture, pngPath, spriteClips, buttonsArray)) {
        std::cout << "Failed to load media, aborting program\n";
        return 1;
    }
    
    bool userRequestsQuit = false;

    SDL_Event event;

    while(!userRequestsQuit) {
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT) {
                userRequestsQuit = true;
            }

            for (int i = 0; i < gButtonConstants::TOTAL_BUTTONS; ++i) {
                buttonsArray[i].handleMouseEvent(&event);            
            }
        }

        SDL_SetRenderDrawColor(&currentWindow.getRenderer(), WHITE::red_rgba, WHITE::green_rgba, WHITE::blue_rgba, WHITE::alpha_rgba);
        SDL_RenderClear(&currentWindow.getRenderer());

        for (int i = 0; i < gButtonConstants::TOTAL_BUTTONS; ++i) {
            buttonsArray[i].renderButtonSprite(buttonTexture, currentWindow, spriteClips);
        }

        //This function updates the screen
        SDL_RenderPresent(&currentWindow.getRenderer());
    }

    IMG_Quit();
    SDL_Quit();

    return 0;
}