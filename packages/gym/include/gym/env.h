#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <graphics/colors.h>
#include <graphics/2d/entities.h>
#include <graphics/2d/screen.h>

namespace Gym {
    class Env {
        public:
            Env (const std::string& configPath);
            ~Env();
            std::unique_ptr<Graphics::Screen> screen;
            void step();
            void render(Graphics::Color color);
            void addEntity(Graphics::Entity);
        private:
            int fps;
            std::vector<Graphics::Entity> entities;
    };
}