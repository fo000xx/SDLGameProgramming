#include <iostream>
#include <string>
#include <memory>
#include <array>
#include <SDL2/SDL_image.h>
#include "LWindow.h"
#include "LTexture.h"
#include "colours.h"

int main()
{
    LWindow currentWindow{};
 
    LTexture modulatedTexture;
    std::string fadeoutPath{ "fadeout.png"};
    if(!currentWindow.loadMedia(modulatedTexture, fadeoutPath)) {
        std::cout << "Failed to load front media, aborting program\n";
        return 1;
    }
    
    modulatedTexture.setBlendMode(SDL_BLENDMODE_BLEND);

    LTexture backgroundTexture;
    std::string fadeinPath{"fadein.png"};
    if(!currentWindow.loadMedia(backgroundTexture, fadeinPath)) {
        std::cout << "Failed to load back media, aborting program\n";
        return 1;
    }

    bool userRequestsQuit = false;

    SDL_Event eventHandler;

    Uint8 alpha{ 255 };

    while(!userRequestsQuit) {
        while(SDL_PollEvent(&eventHandler) != 0) {
            if(eventHandler.type == SDL_QUIT) {
                userRequestsQuit = true;
            }
            else if (eventHandler.type == SDL_KEYDOWN) {
                if (eventHandler.key.keysym.sym == SDLK_w) {
                    if (alpha + 32 > 255) { alpha = 255; }
                    else { alpha += 32; }
                }
                if (eventHandler.key.keysym.sym == SDLK_s) {
                    if (alpha - 32 < 0) { alpha = 0; }
                    else {alpha -= 32; }
                }
            }
        }

        SDL_SetRenderDrawColor(&currentWindow.getRenderer(), WHITE::red_rgba, WHITE::green_rgba, WHITE::blue_rgba, WHITE::alpha_rgba);
        SDL_RenderClear(&currentWindow.getRenderer());

        backgroundTexture.renderTexture(0, 0, currentWindow);
        modulatedTexture.setAlpha(alpha);
        modulatedTexture.renderTexture(0,0, currentWindow);

        SDL_RenderPresent(&currentWindow.getRenderer());
    }

    IMG_Quit();
    SDL_Quit();

    return 0;
}