#pragma once
#include <string>

namespace Canis
{
    enum WindowFlags
    {
        FULLSCREEN = 1,
        BORDERLESS = 16
    };

    class Window
    {
    public:
        Window();
        ~Window();

        int CreateFullScreen(std::string _windowName);
        int Create(std::string _windowName, int _screenWidth, int _screenHeight, unsigned int _currentFlags);
        void SetWindowName(std::string _windowName);

        void SwapBuffer();
        void MouseLock(bool _isLocked);
        bool GetMouseLock() { return m_mouseLock; }

        int GetScreenWidth() { return m_screenWidth; }
        int GetScreenHeight() { return m_screenHeight; }

        void* GetSDLWindow() { return m_sdlWindow; }
        void* GetGLContext() { return m_glContext; }

        void ToggleFullScreen();

        float fps;

    private:
        void *m_sdlWindow;
        void *m_glContext;
        int m_screenWidth, m_screenHeight;
        bool m_fullscreen = false;
        bool m_mouseLock = false;
    };
} // end of Canis namespace