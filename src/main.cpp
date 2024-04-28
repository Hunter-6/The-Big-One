#include <SDL.h>
#include <SDL_image.h>
#include "Background.h"
#include "PLayer.h"
#include <iostream>

// const int SCREEN_WIDTH = 800;
// const int SCREEN_HEIGHT = 600;
// const int NUMBER_OF_LAYERS = 12;
// const int LAYER_HEIGHT = 0.75;

int main(int argv, char* argc[]) {
    // Khởi tạo SDL và SDL_Image
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Tạo cửa sổ SDL
    SDL_Window* window = SDL_CreateWindow("Bloody RED HOOD ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Tạo renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Tạo đối tượng Background
    Background background(renderer, "assets/Background layers", NUMBER_OF_LAYERS, SCREEN_WIDTH, SCREEN_HEIGHT, LAYER_HEIGHT);

    //Tạo đối tượng player
    Player player(renderer, "assets/Player/idle", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 9, 20, 40);

    // Vòng lặp chính của game
    bool quit = false;
    while (!quit) {
        // Xử lý sự kiện
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            player.handleInput(event);
        }

        // Xóa màn hình
        SDL_RenderClear(renderer);

        // Vẽ background
        background.render();

        //cập nhật trạng thái player
        player.update();

        //vẽ player lên màn hình
        player.render();

        // Cập nhật màn hình
        SDL_RenderPresent(renderer);
    }

    // Giải phóng tài nguyên và thoát
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
