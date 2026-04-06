#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <physics/2d/geom.h>
#include <graphics/colors.h>
#include <graphics/2d/entities.h>
#include <gym/env.h>


const std::string configPath = std::string(CARTPOLE_SRC_DIR) + "/src/config.json";

int main(int argc, char* argv[]) {


    Gym::Env env = Gym::Env(configPath);


    Graphics::Color backgroundColor = Graphics::Colors::White;

    Physics::Circle shape1 = Physics::Circle(Physics::Vec2D(100,400), 10);
    Physics::RegularPolygon shape2 = Physics::RegularPolygon(Physics::Vec2D(600,400), 3, 10);
    Physics::RegularPolygon shape3 = Physics::RegularPolygon(Physics::Vec2D(500,500), 4, 10);
    Physics::RegularPolygon shape4 = Physics::RegularPolygon(Physics::Vec2D(500,100), 6, 10);


    Graphics::Entity entity1 = Graphics::Entity(Physics::Object(shape1), Graphics::Colors::Black);
    Graphics::Entity entity2 = Graphics::Entity(Physics::Object(shape2), Graphics::Colors::Black);
    Graphics::Entity entity3 = Graphics::Entity(Physics::Object(shape3), Graphics::Colors::Black);
    Graphics::Entity entity4 = Graphics::Entity(Physics::Object(shape4), Graphics::Colors::Black);


    env.addEntity(entity1);
    env.addEntity(entity2);
    env.addEntity(entity3);
    env.addEntity(entity4);

    
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
        env.render(backgroundColor);
    }

    return 0;
}