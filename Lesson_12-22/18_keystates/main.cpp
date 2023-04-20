#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <string>
#include <memory>
#include <array>
#include <cstdint>
#include <SDL2/SDL_image.h>
#include "LWindow.h"
#include "LTexture.h"
#include "colours.h"
#include "globalConstants.h"

int main()
{
    LWindow currentWindow{};

    LTexture pressTexture{};
    LTexture upTexture{};
    LTexture downTexture{};
    LTexture leftTexture{};
    LTexture rightTexture{};

    std::array<std::string, gConstants::numOfTextures> pathArray{ "press.png", "right.png", "down.png", "left.png", "up.png"};
    std::array<LTexture*, gConstants::numOfTextures> textureArray{ &pressTexture, &rightTexture, &downTexture, &leftTexture, &upTexture };
    //std::string 
    if(!currentWindow.loadMedia(textureArray, pathArray)) {
        std::cout << "Failed to load media, aborting program\n";
        return 1;
    }
    
    bool userRequestsQuit = false;

    SDL_Event eventHandler;

    //std::unique_ptr<LTexture> currentTexture{ nullptr };
    LTexture* currentTexture = NULL;

    while(!userRequestsQuit) {
        while(SDL_PollEvent(&eventHandler) != 0) {
            if(eventHandler.type == SDL_QUIT) {
                userRequestsQuit = true;
            }
        }

        const uint8_t* currentKeyStates{ SDL_GetKeyboardState(NULL) };
        //std::unique_ptr<const uint8_t> currentKeyStates{ SDL_GetKeyboardState(NULL) };
        if (currentKeyStates[SDL_SCANCODE_UP]) {
            currentTexture = &upTexture;
        }
        else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
            currentTexture = &downTexture;
        }
        else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            currentTexture = &leftTexture;
        }
        else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            currentTexture = &rightTexture;
        }
        else {
            currentTexture = &pressTexture;
        }

        SDL_SetRenderDrawColor(&currentWindow.getRenderer(), WHITE::red_rgba, WHITE::green_rgba, WHITE::blue_rgba, WHITE::alpha_rgba);
        SDL_RenderClear(&currentWindow.getRenderer());

        currentTexture->renderTexture(0, 0, currentWindow);

        //This function updates the screen
        SDL_RenderPresent(&currentWindow.getRenderer());
    }

    IMG_Quit();
    SDL_Quit();

    return 0;
}
