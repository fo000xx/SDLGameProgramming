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

    if(!currentWindow.loadMedia(modulatedTexture)) {
        std::cout << "Failed to load media, aborting program\n";
        return 1;
    }

    bool userRequestsQuit = false;

    SDL_Event eventHandler;

    Uint8 red{ 255 };
    Uint8 green{ 255 };
    Uint8 blue{ 255 };

    while(!userRequestsQuit) {
        while(SDL_PollEvent(&eventHandler) != 0) {
            if(eventHandler.type == SDL_QUIT) {
                userRequestsQuit = true;
            }
            else if (eventHandler.type == SDL_KEYDOWN) {
                switch(eventHandler.key.keysym.sym) {
                    case SDLK_q: red += 32; break;
                    case SDLK_w: green += 32; break;
                    case SDLK_e: blue += 32; break;
                    case SDLK_a: red -= 32; break;
                    case SDLK_s: green -= 32; break;
                    case SDLK_d: blue -= 32; break;
                }
            }
        }

        SDL_SetRenderDrawColor(&currentWindow.getRenderer(), WHITE::red_rgba, WHITE::green_rgba, WHITE::blue_rgba, WHITE::alpha_rgba);
        SDL_RenderClear(&currentWindow.getRenderer());

        modulatedTexture.setColour(red, green, blue);
        modulatedTexture.renderTexture(0, 0, currentWindow);

        SDL_RenderPresent(&currentWindow.getRenderer());
    }

    IMG_Quit();
    SDL_Quit();

    return 0;
}