#pragma once
#include <SDL3/SDL.h>
#include "graphics/colors.h"
#include <physics/2d/shapes.h>

namespace Graphics {
    class Screen {
    public:
        Screen(std::string title, int height, int width);
        ~Screen();
        int height;
        int width;
        void present();
        void drawBackground(Color color);
        void drawEntity(const Physics::Circle& circle, Color color, int transparency = 255);
        void drawEntity(const Physics::RegularPolygon& polygon, Color color, int transparency = 255);
    private:
        std::string title;
        SDL_Window* window;
        SDL_Renderer* renderer;
    };
}