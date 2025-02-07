#include "Window.hpp"
#include <SDL.h>
#include <GL/glew.h>
#include <iostream>

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
        
        if (m_sdlWindow == nullptr)
        {
            return 1; // failed to open window
        }

        m_glContext = (void*)SDL_GL_CreateContext((SDL_Window*)m_sdlWindow);

        if (m_glContext == nullptr)
        {
            return 2; // failed to create gl context
        }

        GLenum error = glewInit();

        if (error != GLEW_OK)
        {
            return 3;
        }

        const char* openGLVersion = (const char*)glGetString(GL_VERSION);
        std::cout << openGLVersion << std::endl;

        ClearColor();

        // VSYNC 0 off 1 on
        SDL_GL_SetSwapInterval(1);

        // Enable alpha blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        return 0;
    }

    void Window::Swap() {
        // After we draw our sprite and models to a window buffer
        // We want to display the one we were drawing to and
        // get the old buffer to start drawing our next frame to
        SDL_GL_SwapWindow((SDL_Window*)m_sdlWindow);
    }

    void Window::ClearColor() {
        // before a new frame is drawn we need to clear the buffer
        // the clear color will be the new value of all of the pixels
        // in that buffer
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    }
}