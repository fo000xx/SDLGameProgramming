#include "LButton.h"
#include "LTexture.h"
#include "globalConstants.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>

#include <iostream>

LButton::LButton()
{
    mTopLeftPosition.x = 0;
    mTopLeftPosition.y = 0;

    mCurrentSprite = LButtonSprite::BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setTopLeftPosition(int x, int y)
{
    mTopLeftPosition.x = x;
    mTopLeftPosition.y = y;
}

void LButton::handleMouseEvent(SDL_Event* event)
{
    int mouseXCoord;
    int mouseYCoord;
    if(!(event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONDOWN)) {
        return;
    }
    
    SDL_GetMouseState(&mouseXCoord, &mouseYCoord);

    bool isMouseOnButton{ true }; 
    if (mouseXCoord < mTopLeftPosition.x ) { isMouseOnButton = false; }
    if (mouseXCoord > mTopLeftPosition.x + gButtonConstants::BUTTON_WIDTH) { isMouseOnButton = false; }
    if (mouseYCoord < mTopLeftPosition.y ) { isMouseOnButton = false; }
    if (mouseYCoord > mTopLeftPosition.y + gButtonConstants::BUTTON_HEIGHT) { isMouseOnButton = false; }
    if (!isMouseOnButton) {
        mCurrentSprite = LButtonSprite::BUTTON_SPRITE_MOUSE_OUT;
    }
    else {
        switch(event->type)
        {
            case SDL_MOUSEMOTION: mCurrentSprite = LButtonSprite::BUTTON_SPRITE_MOUSE_OVER_MOTION; break;
            case SDL_MOUSEBUTTONDOWN: mCurrentSprite = LButtonSprite::BUTTON_SPRITE_MOUSE_DOWN; break;
            case SDL_MOUSEBUTTONUP: mCurrentSprite = LButtonSprite::BUTTON_SPRITE_MOUSE_UP; break;
        }
    }
}

void LButton::renderButtonSprite(LTexture& buttonTexture, LWindow& currentWindow, std::array<SDL_Rect, LButtonSprite::BUTTON_SPRITE_TOTAL>& spriteClips)
{
    buttonTexture.renderTexture(mTopLeftPosition.x, mTopLeftPosition.y, currentWindow, &spriteClips[mCurrentSprite]);
}