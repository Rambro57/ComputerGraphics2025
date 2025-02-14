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
#include "Canis/InputManager.hpp"

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

    Canis::InputManager inputManager;

    while(inputManager.Update(window.GetScreenWidth(), window.GetScreenHeight()))
    {
        

        glClearColor(
            inputManager.mouse.x/window.GetScreenWidth(),
            inputManager.mouse.y/window.GetScreenHeight(),
            sin((float)SDL_GetTicks()/1000.0f), 1.0f);
        
        glClear(GL_COLOR_BUFFER_BIT);

        //Canis::Log("Mouse Pos: " + glm::to_string(mousePos));
        window.SwapBuffer();
    }

    return 0;
}