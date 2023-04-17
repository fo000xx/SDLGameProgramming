#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <memory>
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

    void renderTexture(int x, int y, LWindow& currentWindow, SDL_Rect* textureSegment = NULL);

    void setColour(Uint8 red, Uint8 green, Uint8 blue);

    void setBlendMode(SDL_BlendMode blending);

    void setAlpha(Uint8 alpha);

private:
    std::unique_ptr<SDL_Texture, customDeleter<SDL_Texture>> mTexture{};
    
    int mTextureWidth{};
    int mTextureHeight{};
};

#endif