#include "Window.hpp"
#include <SDL.h>

namespace Canis
{
    int Window::Create() {
        m_width = 640;
        m_height = 360;

        SDL_CreateWindow("Computer Graphics",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, 
            m_width, m_height, 0);
            
        return 0;
    }
    void Window::Swap() {

    }
    void Window::ClearColor() {

    }
}