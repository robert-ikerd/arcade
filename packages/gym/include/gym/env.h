#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <graphics/colors.h>
#include <graphics/2d/entities.h>
#include <graphics/2d/screen.h>

namespace Gym {
    enum class Mode {
        PLAY,
        TRAIN_HEADLESS,
        TRAIN_SCREEN
    };
    class Env {
        public:
            Env (const std::string& configPath, Mode mode=Mode::PLAY);
            ~Env();
            std::unique_ptr<Graphics::Screen> screen;
            void step();
            void render(Graphics::Color color);
            void addEntity(Graphics::Entity);
        private:
            Mode mode;
            int fps;
            std::vector<Graphics::Entity> entities;
    };
}