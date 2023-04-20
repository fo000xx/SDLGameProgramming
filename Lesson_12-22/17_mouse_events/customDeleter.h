
#ifndef CUSTOMDELETER_H
#define CUSTOMDELETER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

template<typename T>
struct customDeleter
{
    void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
    void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
    void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
    void operator()(SDL_Surface *p) const { SDL_FreeSurface(p); }
    
    #if defined(SDL_TTF_MAJOR_VERSION)
    void operator()(TTF_Font *p) const { TTF_CloseFont(p); }
    #endif
};

#endif