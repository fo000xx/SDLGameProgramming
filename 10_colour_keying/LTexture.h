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
    //constructor
    LTexture() : m_Width{ 0 }, m_Height{ 0 }, m_Texture{}
    {
    }

    //clears current texture
    void free();

    //loads image at specified path
    bool loadFromFile(std::string path, LWindow& currentWindow);

    //renders texture at given point
    void render(int x, int y, LWindow& currentWindow);

    //gets image dimensions
    int getWidth() { return m_Width; }
    int getHeight() { return m_Height; }

private:
    //actual hardware texture
    std::unique_ptr<SDL_Texture, custom_deleter<SDL_Texture>> m_Texture{};
    
    //image dimensions
    int m_Width{};
    int m_Height{};
};

#endif