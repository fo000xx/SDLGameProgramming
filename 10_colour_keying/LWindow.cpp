#include <memory>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "LWindow.h"
#include "LTexture.h"

bool LWindow::loadMedia(LTexture& fooTexture, LTexture& backgroundTexture)
{
    if (!fooTexture.loadFromFile("foo.png", *this)) {
       std::cout << "Failed to load Foo' texture image!\n";
       return false;
    }

    if (!backgroundTexture.loadFromFile("background.png", *this)) {
        std::cout << "Failed to load background texture image!\n";
        return false;
    }

    return true;
}