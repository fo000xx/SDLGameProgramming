#include <string>
#include <memory>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "LWindow.h"
#include "colours.h"
#include "customDeleter.h"

bool LTexture::loadFromFile(std::string& path, LWindow& currentWindow)
{
    resetTextureParams();

    auto* rawLoadedSurface = IMG_Load(path.c_str());
    if(rawLoadedSurface == NULL) {
        std::cout << "Unable to load image " << path.c_str() << "! SDL Error: " << IMG_GetError() << '\n';
        return false;
    }

    std::unique_ptr<SDL_Surface, customDeleter<SDL_Surface>> RAIILoadedSurface{rawLoadedSurface};
    SDL_SetColorKey(RAIILoadedSurface.get(), SDL_TRUE, SDL_MapRGB(RAIILoadedSurface->format, CYAN::red_rgba, CYAN::green_rgba, CYAN::blue_rgba));

    auto* newRawTexture = SDL_CreateTextureFromSurface(&currentWindow.getRenderer(), RAIILoadedSurface.get());
    if(newRawTexture == NULL) {
        std::cout << "Unable to create texture from " << path.c_str() << " SDL Error: " << SDL_GetError() << '\n';
        return false;
    }

    mTextureWidth = RAIILoadedSurface->w;
    mTextureHeight = RAIILoadedSurface->h;

    mTexture.reset(std::move(newRawTexture));
    
    if (mTexture == NULL) {
        std::cout << "Texture move has failed\n";
        return false;
    }

    return true;
}

void LTexture::resetTextureParams()
{
    if (mTexture != NULL) {
        mTextureWidth = 0;
        mTextureHeight = 0;
    }
}

void LTexture::renderTexture(int x, int y, LWindow& currentWindow, SDL_Rect* textureSegment, double angleOfSeg, SDL_Point* centreofSeg, SDL_RendererFlip flipState)
{
    SDL_Rect renderArea{ x, y, mTextureWidth, mTextureHeight };

    if(textureSegment != NULL) {
        renderArea.w = textureSegment->w;
        renderArea.h = textureSegment->h;
    }

    SDL_RenderCopyEx(&currentWindow.getRenderer(), mTexture.get(), textureSegment, &renderArea, angleOfSeg, centreofSeg, flipState);
}

void LTexture::setColour(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(mTexture.get(), red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture.get(), blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture.get(), alpha);
}
