#ifndef LBUTTON_H
#define LBUTTON_H

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "buttonSprites.h"
#include "customDeleter.h"

class LWindow;

class LButton
{
public:
    LButton();

    void setTopLeftPosition(int x, int y);

    void handleMouseEvent(SDL_Event* event);

    void renderButtonSprite(LTexture& buttonTexture, LWindow& currentWindow, std::array<SDL_Rect, LButtonSprite::BUTTON_SPRITE_TOTAL>& spriteClips);

private:    
    SDL_Point mTopLeftPosition{};
    LButtonSprite mCurrentSprite{};
};

#endif