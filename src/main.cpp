
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"
#include "logic.h"

using namespace std;

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void processClick(int x, int y, Tictactoe& game) {

    int boardWidth = BOARD_SIZE * CELL_SIZE;
    int boardHeight = BOARD_SIZE * CELL_SIZE;
    int boardX = (SCREEN_HEIGHT - boardWidth)/2;
    int boardY = (SCREEN_HEIGHT - boardHeight)/2;

    int clickedCol = ((x - BOARD_X) / CELL_SIZE) - 7;
    int clickedRow = ((y - BOARD_Y) / CELL_SIZE) - 5;

    if (clickedRow >= 0 && clickedRow < BOARD_SIZE && clickedCol >= 0 && clickedCol < BOARD_SIZE) {
        game.move(clickedRow, clickedCol);
    }
}

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    Tictactoe game;
    game.init();
    graphics.render(game);

    int x, y;
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_m) {
                        game.showMines = !game.showMines;
                        SDL_RenderClear(graphics.renderer);  // Clear the renderer
                        graphics.render(game);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x, &y);
                    processClick(x, y, game);
                    SDL_RenderClear(graphics.renderer);  // Clear the renderer
                    graphics.render(game);
                    break;
            }
        }
        SDL_Delay(100);
    }

    graphics.quit();
    SDL_Quit();

    return 0;
}
