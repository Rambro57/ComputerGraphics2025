#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>

#include <SDL.h>

#include "Canis/Canis.hpp"
#include "Canis/Window.hpp"

// git restore .
// git fetch
// git pull

#ifdef _WIN32
#define main SDL_main
extern "C" int main(int argc, char* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    Canis::Init();

    Canis::Window window;
    window.Create();
    
    bool running = false;

    while(running)
    {
        
    }

    return 0;
}