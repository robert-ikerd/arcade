#include "graphics/colors.h"
#include "graphics/2d/screen.h"

namespace Graphics {
    Screen::Screen(std::string title, int height, int width) : title(title), height(height), width(width) {
        std::string windowTitle = "Game Env: " + title;
        window = SDL_CreateWindow(windowTitle.c_str(), width, height, SDL_WINDOW_RESIZABLE);
        if (!window) {
            SDL_Log("Window creation failed: %s", SDL_GetError());
            return;
        }
        renderer = SDL_CreateRenderer(window, NULL);
        if (!renderer) {
            SDL_Log("Renderer creation failed: %s", SDL_GetError());
        }
    };
    Screen::~Screen() {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
            SDL_Log("Renderer destroyed.");
        }
        if (window) {
            SDL_DestroyWindow(window);
            SDL_Log("Window destroyed.");
        }
        SDL_Quit();
    }
    void Screen::present() {
        SDL_RenderPresent(renderer);
    }
    void Screen::drawBackground(Color color) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_RenderClear(renderer);
    }
    void Screen::drawEntity(const Physics::Circle& circle, const Color& color, float transparency) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, transparency * 255.0f);

        SDL_RenderLine(renderer, circle.center.x - circle.radius, circle.center.y, circle.center.x + circle.radius, circle.center.y);
        for (int dy=1; dy<circle.radius; dy++) {
            float dx = sqrtf((circle.radius * circle.radius) - (dy * dy));
            SDL_RenderLine(renderer, circle.center.x - dx, circle.center.y + dy, circle.center.x + dx, circle.center.y + dy);
            SDL_RenderLine(renderer, circle.center.x - dx, circle.center.y - dy, circle.center.x + dx, circle.center.y - dy);
        }
    }
    void Screen::drawEntity(const Physics::RegularPolygon& polygon, const Color& color, float transparency) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, transparency * 255.0f);
        SDL_Vertex vertices[polygon.sides];
        std::vector<int> indices;

        for (int i = 0; i < polygon.sides; i++) {
            vertices[i].position.x = polygon.points[i].x;
            vertices[i].position.y = polygon.points[i].y;
            
            vertices[i].color.r = color.r / 255.0f;
            vertices[i].color.g = color.g / 255.0f;
            vertices[i].color.b = color.b / 255.0f;
            vertices[i].color.a = transparency;
        };
        for (int i = 1; i<polygon.sides-1; ++i) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i+1);
        }

        SDL_RenderGeometry(renderer, nullptr, vertices, polygon.sides, indices.data(), indices.size());
    }
}