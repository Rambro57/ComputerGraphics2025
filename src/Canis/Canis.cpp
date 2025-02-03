#include "Canis.hpp"
#include <SDL.h>

namespace Canis
{
    void Init()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
    }
}