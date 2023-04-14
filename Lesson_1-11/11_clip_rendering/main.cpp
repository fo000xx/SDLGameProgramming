#include <iostream>
#include <string>
#include <memory>
#include <array>
#include <SDL2/SDL_image.h>
#include "LWindow.h"
#include "LTexture.h"
#include "colours.h"
#include "SpriteSheetAreas.h"

int main()
{
    LWindow currentWindow{};
 
    std::array<SDL_Rect, 4> spriteClips;
    LTexture spriteSheetTexture;

    if(!currentWindow.loadMedia(spriteSheetTexture, spriteClips)) {
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

        spriteSheetTexture.renderTexture(0, 0, currentWindow, &spriteClips[TopLeft]);
        spriteSheetTexture.renderTexture(currentWindow.getWidth() - spriteClips[TopRight].w, 0, currentWindow, &spriteClips[TopRight]);
        spriteSheetTexture.renderTexture(0, currentWindow.getHeight() - spriteClips[BottomLeft].h, currentWindow, &spriteClips[BottomLeft]);
        spriteSheetTexture.renderTexture(currentWindow.getWidth() - spriteClips[BottomRight].w, currentWindow.getHeight() - spriteClips[BottomRight].h, currentWindow, &spriteClips[BottomRight]);

        SDL_RenderPresent(&currentWindow.getRenderer());
    }

    IMG_Quit();
    SDL_Quit();

    return 0;
}