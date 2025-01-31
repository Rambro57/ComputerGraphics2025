#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>

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
    std::cout << "Hello, World!" << std::endl;
    return 0;
}