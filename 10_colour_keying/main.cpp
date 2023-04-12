#include <iostream>
#include <string>
#include <memory>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
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
        std::cout << "Failed to load media\n";
        //failure case.
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

        SDL_SetRenderDrawColor(&currentWindow.getRenderer(), White::red_rgba, White::green_rgba, White::blue_rgba, White::alpha_rgba);
        SDL_RenderClear(&currentWindow.getRenderer());

        //render textures to their respective co-ords
        backgroundTexture.renderTexture(0,0, currentWindow);
        fooTexture.renderTexture(240, 190, currentWindow);

        SDL_RenderPresent(&currentWindow.getRenderer());
    }

    return 0;
}