#include "Window.hpp"
#include <SDL.h>

namespace Canis
{
    int Window::Create() {
        m_width = 640;
        m_height = 360;

        Uint32 flags = SDL_WINDOW_OPENGL;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        m_sdlWindow = (void*)SDL_CreateWindow("Computer Graphics",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, 
            m_width, m_height, flags);

        return 0;
    }
    void Window::Swap() {

    }
    void Window::ClearColor() {

    }
}