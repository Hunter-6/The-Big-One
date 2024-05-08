#include <SDL.h>
#include <SDL_image.h>
#include "Background.h"
#include "Player.h"
#include <iostream>

// const int SCREEN_WIDTH = 800;
// const int SCREEN_HEIGHT = 600;
// const int NUMBER_OF_LAYERS = 12;
// const float LAYER_HEIGHT = 0.75f;


int main(int argc, char* argv[]) {
    // ... (Khởi tạo SDL, SDL_Image) ...

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

    // Khai báo đường dẫn cho animation của player
    std::vector<std::string> animationPaths = {
        "assets/Player/idles",
        "assets/Player/left",
        "assets/Player/right",
        "assets/Player/attack_left",
        "assets/Player/attack_right"
    };

<<<<<<< HEAD
    // Tạo đối tượng player
    Player player(renderer, animationPaths, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 9, 20, 40);
=======

    //Tạo đối tượng player
    Player player(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 9, 20, 40, animationPaths);
>>>>>>> 1738b14fe0382c4d7ab244b7339f38bd04591d67

    // Vòng lặp chính của game
    bool quit = false;
    while (!quit) {
        // Xử lý sự kiện
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_SPACE:
                        case SDLK_w:
                            player.jump();
                            break;
                        case SDLK_RETURN:
                        case SDLK_a:
                        case SDLK_LEFT:
                            // player.moveLeft();
                            player.attackLeft();
                            break;
                        case SDLK_d:
                        case SDLK_RIGHT:
                            // player.moveRight();
                            player.attackRight();
                            break;
                        // case SDLK_q:
                        //     player.attackLeft();
                        //     break;
                        // case SDLK_e:
                        //     player.attackRight();
                        //     break;
                    }
                    break;
            }
        }

        // Xóa màn hình
        SDL_RenderClear(renderer);

        // Vẽ background
        background.render();

        // Cập nhật trạng thái player
        player.update();

        // Vẽ player lên màn hình
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
