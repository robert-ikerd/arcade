#pragma once
#include <SDL3/SDL.h>
#include "graphics/colors.h"
#include <physics/2d/geom.h>

namespace Graphics {
    class Screen {
    public:
        Screen(std::string title, int height=800, int width=600);
        ~Screen();
        int height;
        int width;
        void present();
        void drawBackground(Color color);
        void drawEntity(const Physics::Circle& circle, const Color& color, int transparency = 255);
        void drawEntity(const Physics::RegularPolygon& polygon, const Color& color, int transparency = 255);
    private:
        std::string title;
        SDL_Window* window;
        SDL_Renderer* renderer;
    };
}