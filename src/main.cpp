#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>

#include <SDL.h>

#include "Canis/Canis.hpp"

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

    SDL_CreateWindow("Computer Graphics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, 0);

    while(true){}

    return 0;
}