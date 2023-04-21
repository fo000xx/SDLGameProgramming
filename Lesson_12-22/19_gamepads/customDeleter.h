
#ifndef CUSTOMDELETER_H
#define CUSTOMDELETER_H

#include <SDL2/SDL_image.h>

template<typename T>
struct customDeleter
{
    void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
    void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
    void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
    void operator()(SDL_Surface *p) const { SDL_FreeSurface(p); }
    void operator()(SDL_Joystick *p) const { SDL_JoystickClose(p); }
};

#endif