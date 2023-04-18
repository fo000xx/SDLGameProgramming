#include <iostream>
#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "LWindow.h"
#include "LTexture.h"
#include "colours.h"

int main()
{
    LWindow currentWindow{};

    LTexture lazyTexture;
    std::string lazyPath{ "lazy.ttf"};

    if(!currentWindow.loadMedia(lazyTexture, lazyPath)) {
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

        lazyTexture.renderTexture((currentWindow.getWidth() - lazyTexture.getWidth()) / 2, (currentWindow.getHeight() - lazyTexture.getHeight()) / 2, currentWindow);

        //This function updates the screen
        SDL_RenderPresent(&currentWindow.getRenderer());
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}