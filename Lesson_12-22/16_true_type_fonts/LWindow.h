#ifndef LWINDOW_H
#define LWINDOW_H

#include <memory>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "colours.h"
#include "customDeleter.h"

class LWindow;
class LTexture;

class LWindow
{
public:
    LWindow();

    bool loadMedia(LTexture& texture, std::string& path);

    SDL_Renderer& getRenderer(){ return *mRenderer; }
    int getHeight(){ return SCREEN_HEIGHT; }
    int getWidth(){ return SCREEN_WIDTH; }
    
private:
    const int SCREEN_WIDTH{ 640 };
    const int SCREEN_HEIGHT{ 480 };
    
    std::unique_ptr<SDL_Window, customDeleter<SDL_Window>> mWindow{};
    std::unique_ptr<SDL_Renderer, customDeleter<SDL_Renderer>> mRenderer{};
};

#endif