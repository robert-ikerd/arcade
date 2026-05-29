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
        if (!TTF_Init()) {
            SDL_Log("TTF Initialization failed: %s", SDL_GetError());
            return;
        }
        std::string fontPath = "/System/Library/Fonts/Supplemental/Arial.ttf";
        font = TTF_OpenFont(fontPath.c_str(), 18); // 18pt size
        if (!font) {
            SDL_Log("Font loading failed: %s. Defaulting text to debug font.", SDL_GetError());
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
        if (font) {
            TTF_CloseFont(font);
            SDL_Log("Font closed.");
        }
        TTF_Quit();
        SDL_Log("TTF Subsystem closed.");
        SDL_Quit();
    }
    void Screen::present() {
        SDL_RenderPresent(renderer);
    }
    void Screen::drawBackground(Color color) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_RenderClear(renderer);
    }
    void Screen::writeText(std::string text, Graphics::Color color, int x, int y) {
        SDL_Color sdlColor = { color.r, color.g, color.b, 255 };
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), text.length(), sdlColor);
        if (!textSurface) return;
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture) {
            SDL_FRect dstRect = { 
                static_cast<float>(x), 
                static_cast<float>(y), 
                static_cast<float>(textSurface->w), 
                static_cast<float>(textSurface->h) 
            };
            SDL_RenderTexture(renderer, textTexture, nullptr, &dstRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_DestroySurface(textSurface);
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
    void Screen::drawEntity(const Physics::CustomPolygon& polygon, const Color& color, float transparency) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, transparency * 255.0f);
        int num_points = polygon.points.size();
        SDL_Vertex vertices[num_points];
        std::vector<int> indices;

        for (int i = 0; i < num_points; i++) {
            vertices[i].position.x = polygon.points[i].x;
            vertices[i].position.y = polygon.points[i].y;
            
            vertices[i].color.r = color.r / 255.0f;
            vertices[i].color.g = color.g / 255.0f;
            vertices[i].color.b = color.b / 255.0f;
            vertices[i].color.a = transparency;
        };
        for (int i = 1; i<num_points-1; ++i) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i+1);
        }

        SDL_RenderGeometry(renderer, nullptr, vertices, num_points, indices.data(), indices.size());
    }
}