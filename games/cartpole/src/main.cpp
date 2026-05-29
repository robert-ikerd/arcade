#include <iostream>
#include <random>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <physics/2d/geom.h>
#include <graphics/colors.h>
#include <graphics/2d/entities.h>
#include <gym/env.h>


const std::string configPath = std::string(CARTPOLE_SRC_DIR) + "/src/config.json";

int main(int argc, char* argv[]) {

    const int w = 800;
    const int h = 600;
    Physics::Vec2D center = Physics::Vec2D(w/2, 2*h/3);

    Gym::Env env = Gym::Env(configPath);


    Graphics::Color backgroundColor = Graphics::Colors::White;

    std::vector<Physics::Vec2D> cartFrame;
    cartFrame.emplace_back(center.x-30.0f, center.y-15.0f);
    cartFrame.emplace_back(center.x+30.0f, center.y-15.0f);
    cartFrame.emplace_back(center.x+30.0f, center.y+15.0f);
    cartFrame.emplace_back(center.x-30.0f, center.y+15.0f);

    Physics::CustomPolygon cart = Physics::CustomPolygon(center, cartFrame);


    std::vector<Physics::Vec2D> poleFrame;
    Physics::Vec2D poleCenter = Physics::Vec2D(center.x, center.y-10.0f);
    poleFrame.emplace_back(poleCenter.x-3.0f, poleCenter.y);
    poleFrame.emplace_back(poleCenter.x+3.0f, poleCenter.y);
    poleFrame.emplace_back(poleCenter.x+3.0f, poleCenter.y-60.0f);
    poleFrame.emplace_back(poleCenter.x-3.0f, poleCenter.y-60.0f);

    static std::random_device rd;
    static std::mt19937 generator(rd());
    double maxAngle = 0.1;
    std::uniform_real_distribution<float> distribution(-maxAngle, maxAngle);

    Physics::CustomPolygon pole = Physics::CustomPolygon(poleCenter, poleFrame);
    pole.rotate(distribution(generator));

    std::uniform_real_distribution<float> speed_distribution(-1, 1);
    Physics::Vec2D cartSpeed = {speed_distribution(generator), 0.0};

    Graphics::Entity cartEntity = Graphics::Entity(Physics::Object(cart), Graphics::Colors::Black);
    Graphics::Entity poleEntity = Graphics::Entity(Physics::Object(pole), Graphics::Colors::Orange);

    cartEntity.object.setVelocity(cartSpeed);
    poleEntity.object.setVelocity(cartSpeed);

    env.addEntity(cartEntity);
    env.addEntity(poleEntity);

    SDL_Event event;

    while (env.running) {
        Gym::AdminAction adminActions = Gym::AdminAction::NONE;

        while (SDL_PollEvent(&event)) {
            adminActions |= env.parseAdminAction(event);
        }
        env.handleAdminActions(adminActions);

        if (~env.paused) {
            auto& livePoleEntity = env.entities[1];
            float currentAngle = 0.0f;
            std::visit([&currentAngle](const auto& shape) {
                currentAngle = shape.yaw; 
                std::cout << "Current Pole Angle (Yaw): " << shape.yaw << std::endl;
                std::cout << "Current DDTheta : " << std::sin(currentAngle) << std::endl;
            }, livePoleEntity.object.body);
            livePoleEntity.object.setDDTheta(0.01 * std::sin(currentAngle));
            env.step();
            env.render(backgroundColor);
        }

    }

    return 0;
}