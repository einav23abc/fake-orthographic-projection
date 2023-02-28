#include "Window.hpp"
#include <Windows.h>

#define FPS 60
#define FRAME_DELAY (1000/FPS)

Window* window = nullptr;

int main ( int argc , char *argv[] ) {
    
    //FreeConsole();

    Uint32 frameStart;
    int frameTime;

    window = new Window( "window name" , 100 , 100 , 600 , 300 , 160 , 90 , true, false );


    while ( window->running() ){
        frameStart = SDL_GetTicks();

        window->handleEvents();
        window->update();
        window->render();

        frameTime = SDL_GetTicks() - frameStart;
        std::cout << "dt:" << frameTime-FRAME_DELAY << "\n";
        if ( FRAME_DELAY > frameTime ){
            SDL_Delay( FRAME_DELAY - frameTime );
        };
    };

    window->clean();
    
    return 0;
};