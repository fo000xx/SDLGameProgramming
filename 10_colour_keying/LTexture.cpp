#include <string>
#include <memory>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "LWindow.h"


bool LTexture::loadFromFile(std::string path, LWindow& currentWindow)
{
    //get rid of preexisting texture
    free();

    //final texture
    std::unique_ptr<SDL_Texture, custom_deleter<SDL_Texture>> newTexture{};

    //load image at specified path
    std::unique_ptr<SDL_Surface, custom_deleter<SDL_Surface>> loadedSurface{};
    loadedSurface.reset(IMG_Load(path.c_str()));
    if(loadedSurface == NULL)
    {
        std::cout << "Unable to load image " << path.c_str() << "! SDL Error: " << IMG_GetError() << '\n';
    }
    else 
    {
        //colour key image
        SDL_SetColorKey(loadedSurface.get(), SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        
        //create texture from surface pixels
        newTexture.reset(SDL_CreateTextureFromSurface(currentWindow.m_Renderer.get(), loadedSurface.get()));
        if(newTexture == NULL)
        {
            std::cout << "Unable to create texture from " << path.c_str() << " SDL Error: " << SDL_GetError() << '\n';
        }
        else {
            //get image dimensions
            m_Width = loadedSurface->w;
            m_Height = loadedSurface->h;
        }

        //get rid of old loaded surface
        SDL_FreeSurface(loadedSurface.get());
    }

    //return success
    m_Texture.reset(newTexture.get());
    return m_Texture.get() != NULL;
}

void LTexture::free()
{
    //reset the texture
    if (m_Texture != NULL) {
        m_Width = 0;
        m_Height = 0;
    }
}

void LTexture::render(int x, int y, LWindow& currentWindow)
{
    //set rendering space and render to screen
    SDL_Rect renderQuad{ x, y, m_Width, m_Height };
    SDL_RenderCopy(currentWindow.m_Renderer.get(), m_Texture.get(), NULL, &renderQuad);
}