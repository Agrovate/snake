#include<stdio.h>
#include<SDL.h>
#include <stdbool.h>

#define WIDTH 680
#define HEIGHT 480

int main() {
    printf("Hello snake");
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
                    "Snake Game",
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    WIDTH,
                    HEIGHT,
                    0
    );

    bool is_running = true;
    SDL_Event event;

    while (is_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_running = false;
            }
        }
        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
