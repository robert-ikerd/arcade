#include <queue>
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
    enum class AdminAction : uint8_t {
        NONE  = 0,
        QUIT  = 1 << 0,
        PAUSE = 1 << 1,
        RESET = 1 << 2,
        DEBUG = 1 << 3
    };
    inline AdminAction operator|(AdminAction a, AdminAction b) {
        return static_cast<AdminAction>(
            static_cast<uint8_t>(a) | static_cast<uint8_t>(b)
        );
    }
    inline AdminAction& operator|=(AdminAction& a, AdminAction b) {
        a = a | b;
        return a;
    }
    inline bool operator&(AdminAction a, AdminAction b) {
        return (static_cast<uint8_t>(a) & static_cast<uint8_t>(b)) != 0;
    }
    class Env {
        public:
            Env (const std::string& configPath, Mode mode=Mode::PLAY);
            ~Env();
            std::unique_ptr<Graphics::Screen> screen;
            bool running = true;
            bool paused = false;
            bool gameRunning = false;
            bool debugOpen = false;
            AdminAction parseAdminAction(const SDL_Event& event);
            void handleAdminActions(AdminAction actions);
            void step();
            void render(Graphics::Color color);
            void addEntity(Graphics::Entity);
            std::pair<float, float> processPhysics(float action);
            std::vector<Graphics::Entity> entities;
        private:
            Mode mode;
            int fps;
            Uint64 mspf;
            double fpsActual;
            Uint64 tsStart;
            int numFrames;
            int framesPerCalculation;
    };
}