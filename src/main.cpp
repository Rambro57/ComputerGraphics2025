#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>

#include <SDL.h>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Canis/Canis.hpp"
#include "Canis/Debug.hpp"
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
    window.Create("Computer Graphics 2025", 640, 360, 0);
    
    bool running = true;
    glm::vec2 mousePos(0.0f);

    while(running)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEMOTION:
                mousePos.x = event.motion.x;
                mousePos.y = window.GetScreenHeight() - event.motion.y;
                break;
            default:
                break;
            }
        }

        glClearColor(1.0f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Canis::Log("Mouse Pos: " + glm::to_string(mousePos));
        window.SwapBuffer();
    }

    return 0;
}