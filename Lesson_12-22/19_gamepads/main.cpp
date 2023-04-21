#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <string>
#include <memory>
#include <array>
#include <cstdint>
#include <cmath> //for atan2
#include <SDL2/SDL_image.h>
#include "LWindow.h"
#include "LTexture.h"
#include "colours.h"
#include "globalConstants.h"

int main()
{
    LWindow currentWindow{};

    LTexture arrowTexture{};
    std::string arrowPath{ "arrow.png" };

    if(!currentWindow.loadMedia(arrowTexture, arrowPath)) {
        std::cout << "Failed to load media, aborting program\n";
        return 1;
    }
    
    bool userRequestsQuit = false;

    SDL_Event event;

    int xDirection{ 0 };
    int yDirection{ 0 };

    while(!userRequestsQuit) {
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT) {
                userRequestsQuit = true;
            }
            else if (event.type == SDL_JOYAXISMOTION) {
                if (event.jaxis.which == 0) {
                    if (event.jaxis.axis == 0) {
                        if (event.jaxis.value < -gJoystick::JOYSTICK_DEAD_ZONE) {
                            xDirection = -1;
                        }
                        else if (event.jaxis.value > gJoystick::JOYSTICK_DEAD_ZONE) {
                            xDirection = 1;
                        }
                        else {
                            xDirection = 0;
                        }
                    }
                    if (event.jaxis.axis == 1) {
                        if (event.jaxis.value < -gJoystick::JOYSTICK_DEAD_ZONE) {
                            yDirection = -1;
                        }
                        else if (event.jaxis.value > gJoystick::JOYSTICK_DEAD_ZONE) {
                            yDirection = 1;
                        }
                        else {
                            yDirection = 0;
                        }
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(&currentWindow.getRenderer(), WHITE::red_rgba, WHITE::green_rgba, WHITE::blue_rgba, WHITE::alpha_rgba);
        SDL_RenderClear(&currentWindow.getRenderer());

        double joystickAngle{ atan2((double)yDirection, (double)xDirection)* (180.0 / M_PI) };

        if (xDirection == 0 && yDirection == 0) {
            joystickAngle = 0;
        }

        arrowTexture.renderTexture((currentWindow.getWidth() -  arrowTexture.getWidth()) / 2, (currentWindow.getHeight() -  arrowTexture.getHeight()) / 2, currentWindow, NULL, joystickAngle);

        //This function updates the screen
        SDL_RenderPresent(&currentWindow.getRenderer());
    }

    IMG_Quit();
    SDL_Quit();

    return 0;
}