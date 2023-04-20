#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "customDeleter.h"

class LWindow;

//texture wrapping class
class LTexture
{
public:
    LTexture() : mTexture{ nullptr }, mTextureWidth{ 0 }, mTextureHeight{ 0 }
    {
    }

    ~LTexture()
    {
        this->resetTextureParams();
    }

    void resetTextureParams();

    bool loadFromFile(std::string& path, LWindow& currentWindow);
    
    #if defined(SDL_TTF_MAJOR_VERSION)
    bool loadFromRenderedText(std::string textureText, SDL_Color textColour, LWindow& currentWindow);
    #endif

    void renderTexture(int x, int y, LWindow& currentWindow, SDL_Rect* textureSegment = NULL, double angleOfSeg = 0.0, SDL_Point* centreofSeg = NULL, SDL_RendererFlip flipState = SDL_FLIP_NONE);

    void setColour(Uint8 red, Uint8 green, Uint8 blue);

    void setBlendMode(SDL_BlendMode blending);

    void setAlpha(Uint8 alpha);

    int getWidth(){ return mTextureWidth; }
    int getHeight(){ return mTextureHeight; }

private:
    std::unique_ptr<SDL_Texture, customDeleter<SDL_Texture>> mTexture{};
    
    int mTextureWidth{};
    int mTextureHeight{};
};

#endif