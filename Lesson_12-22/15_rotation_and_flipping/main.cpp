#include <SDL2/SDL_render.h>
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

    LTexture arrowTexture;
    std::string arrowPath{ "arrow.png"};

    if(!currentWindow.loadMedia(arrowTexture, arrowPath)) {
        std::cout << "Failed to load front media, aborting program\n";
        return 1;
    }
    
    bool userRequestsQuit = false;

    SDL_Event eventHandler;

    double angleOfSeg{ 0 };
    SDL_RendererFlip flipState{ SDL_FLIP_NONE };

    while(!userRequestsQuit) {
        while(SDL_PollEvent(&eventHandler) != 0) {
            if(eventHandler.type == SDL_QUIT) {
                userRequestsQuit = true;
            }
            else if(eventHandler.type == SDL_KEYDOWN) {
                switch(eventHandler.key.keysym.sym) {
                    case SDLK_a: angleOfSeg -= 60; break;
                    case SDLK_d: angleOfSeg += 60; break;
                    case SDLK_q: flipState = SDL_FLIP_HORIZONTAL; break;
                    case SDLK_e: flipState = SDL_FLIP_VERTICAL; break;
                    case SDLK_w: flipState = SDL_FLIP_NONE; break;
                }
            }
        }

        SDL_SetRenderDrawColor(&currentWindow.getRenderer(), WHITE::red_rgba, WHITE::green_rgba, WHITE::blue_rgba, WHITE::alpha_rgba);
        SDL_RenderClear(&currentWindow.getRenderer());

        arrowTexture.renderTexture((currentWindow.getWidth() - arrowTexture.getWidth()) / 2, (currentWindow.getHeight() - arrowTexture.getHeight()) / 2, currentWindow, NULL, angleOfSeg, NULL, flipState);

        //This function updates the screen
        SDL_RenderPresent(&currentWindow.getRenderer());
    }

    IMG_Quit();
    SDL_Quit();

    return 0;
}