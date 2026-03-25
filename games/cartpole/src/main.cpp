#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <graphics/colors.h>
#include <graphics/2d/screen.h>
#include <physics/2d/shapes.h>



int main(int argc, char* argv[]) {

    Graphics::Screen screen = Graphics::Screen("Cartpole", 800, 600);


    Graphics::Color backgroundColor = Graphics::Colors::Purple;
    
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
        screen.drawBackground(backgroundColor);


        screen.present();
    }

    return 0;
}