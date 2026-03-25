#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

namespace Gym {
    class Env {
        public:
            Env ();
            void step();
    };
}