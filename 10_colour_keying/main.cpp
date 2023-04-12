#include <iostream>
#include <string>
#include <memory>
#include <SDL2/SDL_image.h>
#include "LWindow.h"
#include "LTexture.h"
#include "colours.h"

int main()
{
    LWindow currentWindow{};
    //add failure to initialise error here?

    LTexture fooTexture{};
    LTexture backgroundTexture{}; 
    
    if(!currentWindow.loadMedia(fooTexture, backgroundTexture)) {
        std::cout << "Failed to load media, aborting program\n";
        return 1;
    }

    bool userRequestsQuit = false;

    SDL_Event eventHandler;

    while(!userRequestsQuit) {
        while(SDL_PollEvent(&eventHandler) != 0) {
            if(eventHandler.type == SDL_QUIT) {
                userRequestsQuit = true;
            }
        }

        SDL_SetRenderDrawColor(&currentWindow.getRenderer(), WHITE::red_rgba, WHITE::green_rgba, WHITE::blue_rgba, WHITE::alpha_rgba);
        SDL_RenderClear(&currentWindow.getRenderer());

        //render textures to their respective co-ords
        backgroundTexture.renderTexture(0,0, currentWindow);
        fooTexture.renderTexture(240, 190, currentWindow);

        SDL_RenderPresent(&currentWindow.getRenderer());
    }

    return 0;
}