#include "graphics/colors.h"
#include "graphics/2d/screen.h"

namespace Graphics {
    Screen::Screen(std::string title, int height, int width) : title(title), height(height), width(width) {
        std::string windowTitle = "Game Env: " + title;
        window = SDL_CreateWindow(windowTitle.c_str(), height, width, SDL_WINDOW_RESIZABLE);
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
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderClear(renderer);
    }
    void Screen::drawEntity(const Physics::Circle& circle, Color color) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        for (int w=0; w<circle.radius*2; w++) {
            for (int h=0; h<circle.radius*2; h++) {
                float dx = circle.radius - w;
                float dy = circle.radius - h;
                if ((dx*dx + dy*dy)<=(circle.radius*circle.radius)) {
                    SDL_RenderPoint(renderer, circle.center.x+dx, circle.center.y+dy);
                }
            }
        }
    }
    void Screen::drawEntity(const Physics::RegularPolygon& polygon, Color color) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_Vertex vertices[polygon.sides];

        for (int i = 0; i < polygon.sides; i++) {
            vertices[i].position.x = polygon.points[i].x;
            vertices[i].position.y = polygon.points[i].y;
            
            vertices[i].color.r = color.r / 255.0f;
            vertices[i].color.g = color.g / 255.0f;
            vertices[i].color.b = color.b / 255.0f;
            vertices[i].color.a = color.a / 255.0f;
        };
        SDL_RenderGeometry(renderer, nullptr, vertices, polygon.sides, nullptr, 0);
    }
}