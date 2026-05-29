#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <fstream>
#include <iostream>
#include <gym/json.hpp>
#include "gym/env.h"


using json = nlohmann::json;

namespace Gym {
    Env::Env(const std::string& configPath, Mode mode) : mode(mode) {
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
        if (fps>0) {
            mspf = 1000/fps;
        }
        else {
            mspf = 0;
        }
        tsStart = SDL_GetTicksNS();
        numFrames = 0;
        framesPerCalculation = 30;
        fpsActual = 0;

        screen = std::make_unique<Graphics::Screen>(title, height, width);
    }
    Env::~Env() {}
    AdminAction Env::parseAdminAction(const SDL_Event& event) {
        switch (event.type) {
            case SDL_EVENT_QUIT: {
                return AdminAction::QUIT;
            }
            case SDL_EVENT_KEY_DOWN: {
                switch (event.key.key) {
                    case SDLK_ESCAPE: {
                        return AdminAction::PAUSE;
                    }
                    case SDLK_LCTRL: {
                        return AdminAction::DEBUG;
                    }
                }
            }
        } 
        return AdminAction::NONE;
    }
    void Env::handleAdminActions(AdminAction actions) {
        if (actions & AdminAction::QUIT) {
            running = false;
            return;
        }
        if (actions & AdminAction::PAUSE) {
            paused = !paused;
        }
        if (actions & AdminAction::DEBUG) {
            debugOpen = !debugOpen;
        }
    }
    void Env::step() {
        Uint64 tsCurrent = SDL_GetTicksNS();
        if (numFrames==0) {
            tsStart = SDL_GetTicksNS();
        }
        numFrames += 1;

        if (mode==Mode::PLAY) {
            for (auto& entity : entities) {
                entity.object.processPhysics(); 
            }
            render(Graphics::Colors::White);
        }
        else {
            // float action = determineAction();
            // auto [state, reward] = processPhysics(action);
            running = false;
        } 
        Uint64 tsEnd = SDL_GetTicksNS();
        if (numFrames==framesPerCalculation) {
            fpsActual = 1e9 * numFrames / (tsEnd - tsStart);
            numFrames = 0;
        }
        if (debugOpen && fpsActual>0) {
            std::string fps_text = "FPS: " + std::to_string(static_cast<int>(fpsActual));
            screen->writeText(fps_text, Graphics::Colors::Black, 10, 10);
        }

        Uint64 duration = (tsEnd-tsCurrent) / 1e6;
        if (duration<mspf) {
            SDL_Delay(mspf - duration);
        }
        screen->present();
    }
    void Env::render(Graphics::Color color) {
        screen->drawBackground(color);

        for (const auto& entity : entities) {
            Graphics::Color entityColor = entity.color;
            std::visit([&](const auto& shape) {
                screen->drawEntity(shape, entity.color);
            }, entity.object.body);
        };
    }
    void Env::addEntity(Graphics::Entity entity) {
        entities.push_back(std::move(entity));
    }
}