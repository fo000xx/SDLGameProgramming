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
    LTexture() : mTextureWidth{ 0 }, mTextureHeight{ 0 }, mTexture{ nullptr }
    {
    }

    ~LTexture()
    {
        this->resetTextureParams();
    }

    void resetTextureParams();

    bool loadFromFile(std::string path, LWindow& currentWindow);

    void renderTexture(int x, int y, LWindow& currentWindow);

private:
    std::unique_ptr<SDL_Texture, customDeleter<SDL_Texture>> mTexture{};
    
    int mTextureWidth{};
    int mTextureHeight{};
};

#endif