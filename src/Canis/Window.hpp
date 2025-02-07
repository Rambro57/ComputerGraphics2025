#pragma once
#include <glm/glm.hpp>

namespace Canis
{
    class Window
    {
        public:
            int Create();
            void Swap();
            void ClearColor();
        private:
            void* m_sdlWindow;
            void* m_glContext;
            int m_width;
            int m_height;
            float m_scale;
            glm::vec4 m_clearColor;
    };
}