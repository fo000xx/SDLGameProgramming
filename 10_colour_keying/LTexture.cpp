#include <string>
#include <memory>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "LWindow.h"
#include "colours.h"

bool LTexture::loadFromFile(std::string path, LWindow& currentWindow)
{
    resetTextureParams();

    auto* rawLoadedSurface = IMG_Load(path.c_str());
    if(rawLoadedSurface == NULL) {
        std::cout << "Unable to load image " << path.c_str() << "! SDL Error: " << IMG_GetError() << '\n';
        return false;
    }

    std::unique_ptr<SDL_Surface, customDeleter<SDL_Surface>> RAIILoadedSurface{rawLoadedSurface};
    SDL_SetColorKey(RAIILoadedSurface.get(), SDL_TRUE, SDL_MapRGB(RAIILoadedSurface->format, Cyan::red_rgba, Cyan::green_rgba, Cyan::blue_rgba));

    auto* newRawTexture = SDL_CreateTextureFromSurface(&currentWindow.getRenderer(), RAIILoadedSurface.get());
    if(newRawTexture == NULL)
    {
        std::cout << "Unable to create texture from " << path.c_str() << " SDL Error: " << SDL_GetError() << '\n';
        return false;
    }

    //changing this to the raw pointer wrapped by unique_ptr stops the image loading.
    std::unique_ptr<SDL_Texture, customDeleter<SDL_Texture>> newTexture{};
    newTexture.reset(newRawTexture);

    mTextureWidth = RAIILoadedSurface->w;
    mTextureHeight = RAIILoadedSurface->h;

    //rework so the code is more verbose
    mTexture.reset(newTexture.get());
    return mTexture.get() != NULL;
}

void LTexture::resetTextureParams()
{
    if (mTexture != NULL) {
        mTextureWidth = 0;
        mTextureHeight = 0;
    }
}

void LTexture::renderTexture(int x, int y, LWindow& currentWindow)
{
    SDL_Rect renderArea{ x, y, mTextureWidth, mTextureHeight };
    SDL_RenderCopy(&currentWindow.getRenderer(), mTexture.get(), NULL, &renderArea);
}