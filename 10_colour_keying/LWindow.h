#ifndef LWINDOW_H
#define LWINDOW_H

#include <memory>
#include <SDL2/SDL.h>

#include "customDeleter.h"

class LWindow;
class LTexture;

class LWindow
{
public:
    bool init();

    bool loadMedia(LTexture& fooTexture, LTexture& backgroundTexture, LWindow& currentWindow);

    void close(LTexture& backgroundTexture, LTexture& fooTexture);

    std::unique_ptr<SDL_Renderer, custom_deleter<SDL_Renderer>> &get(){ return  m_Renderer; }
    SDL_Renderer *GetPtr(){ return m_Renderer.get(); }

    friend class LTexture;
    
private:
    //screen dimension constants
    const int SCREEN_WIDTH{ 640 };
    const int SCREEN_HEIGHT{ 480 };
    
    //window to render to
    std::unique_ptr<SDL_Window, custom_deleter<SDL_Window>> m_Window{};

    //window renderer
    std::unique_ptr<SDL_Renderer, custom_deleter<SDL_Renderer>> m_Renderer{};
};

#endif