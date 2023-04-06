#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <string>
#include <memory>

#include "LWindow.h"
#include "LTexture.h"

int main()
{
    //initialize window object
    LWindow currentWindow{};
    
    //initialize texture objects
    LTexture fooTexture{};
    LTexture backgroundTexture{};
    
    //start SDL and create window
    if(!currentWindow.init())
    {
        std::cout << "Failed to initialise\n";
    }
    else
    {
        //load media
        if(!currentWindow.loadMedia(fooTexture, backgroundTexture, currentWindow))
        {
            std::cout << "Failed to load media\n";
        }
        else
        {
            //main loop flag
            bool quit = false;

            //event handler
            SDL_Event e;

            //while applicaiton is running
            while(!quit)
            {
                //handle events on queue
                while(SDL_PollEvent(&e) != 0)
                {
                    //if user requests quit
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }

                //clear screen
                SDL_SetRenderDrawColor(&currentWindow.get(), 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(&currentWindow.get());

                //Render background texture to screen
                backgroundTexture.render(0,0, currentWindow);

                //render Foo' to the screen
                fooTexture.render(240, 190, currentWindow);

                //update screen
                SDL_RenderPresent(&currentWindow.get());
            }
        }
    }

    currentWindow.close(backgroundTexture, fooTexture);
}