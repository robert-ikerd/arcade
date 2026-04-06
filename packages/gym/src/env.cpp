#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <fstream>
#include <gym/json.hpp>
#include "gym/env.h"


using json = nlohmann::json;

namespace Gym {
    Env::Env(const std::string& configPath) {
        std::ifstream configFile(configPath);
        if (!configFile.is_open()) {
            SDL_Log("Could not open config file: %s", configPath.c_str());
            return;
        }

        json data;
        try {
            configFile >> data;
        } catch (json::parse_error& e) {
            SDL_Log("JSON Parse Error: %s", e.what());
            return;
        }

        std::string title = data.value("title", "Untitled");
        int width = data.value("width", 800);
        int height = data.value("height", 600);
        fps = data.value("fps", 60);
        screen = std::make_unique<Graphics::Screen>(title, height, width);
    }
    Env::~Env() {}
    void Env::addEntity(Graphics::Entity entity) {
        entities.push_back(std::move(entity));
    }
    void Gym::Env::render(Graphics::Color color) {
        screen->drawBackground(color);

        for (const auto& entity : entities) {
            Graphics::Color entityColor = entity.color;
            std::visit([&](const auto& shape) {
                screen->drawEntity(shape, entity.color);
            }, entity.object.body);
        };
        
        screen->present();
        }
}