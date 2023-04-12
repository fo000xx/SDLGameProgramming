
#ifndef CUSTOMDELETER_H
#define CUSTOMDELETER_H

#include <SDL2/SDL_image.h>

/*
template<typename T>
struct customDeleter
{
    //does this just use the pointer from the std::unique_ptr?
    void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
    void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
    void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
    void operator()(SDL_Surface *p) const { SDL_FreeSurface(p); }
};
*/

template<typename T>
void customDelete(T* d) {}

template<typename T>
struct customDeleter
{
    void operator()(T* d) const
    {
        customDelete(d);
    }
};

#endif