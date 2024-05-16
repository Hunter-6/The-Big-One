#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "defs.h"
#include "logic.h"
#include "graphics.h"
#include <string>
#include <iostream>
#include <chrono>

void TicTacToe::init() {
        std::memset(mines, false, sizeof(mines));
        std::memset(flags, false, sizeof(flags));
        placeMines(50);  // Randomly place mines
        // std::uniform_int_distribution<> dist(30, 50);
        for (int i = 0; i < BOARD_SIZE; i++){
            for (int j = 0; j < BOARD_SIZE; j++) {
                board[i][j] = EMPTY_CELL;
            }
        }
    }
// TicTacToe::TicTacToe(Graphics& graphics):graphics(graphics){};

    
void TicTacToe::placeMines(int mineCount) {
    static std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());  // Use time-based seeding
    std::uniform_int_distribution<> dist(0, BOARD_SIZE - 1);

    for (int i = 0; i < mineCount; ++i) {
        int row, col;
        do {
            row = dist(rng);
            col = dist(rng);
        } while (mines[row][col]);
        mines[row][col] = true;
    }
}

void TicTacToe::placeFlags(int row, int col){
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && !game_over ){
        flags[row][col] = !flags[row][col];
    } 
}
    
void TicTacToe::move(int row, int column) {
    if (!game_over && board[row][column] == EMPTY_CELL) {
        if (mines[row][column]) {
            std::random_device rd;
            static std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<> dis(0, 5);
            int damage = dis(rng);

            // Apply the damage
            if (nextMove == O_CELL) {
                healthO -= damage;
                board[row][column] = X_CELL;
            } else {
                healthX -= damage;
                board[row][column] = O_CELL;
            }

            std::string message;
            if (damage == 0) {
                message = "Gotcha!!";
            } else if (damage == 1 || damage == 2) {
                message = "Tiny Boom...";
            } else if (damage == 3 || damage == 4) {
                message = "Good BOOM~";
            } else if (damage == 5) {
                message = "HASABULLA! BOOM BOOM BOOM!!!";
            }
            std::cout << message << std::endl;  
            // SDL_Color textColor = {255, 255, 0};
            // graphics.renderText(message, 100, 100, textColor);

            nextMove = (nextMove == O_CELL) ? X_CELL : O_CELL;  
        } else {
            board[row][column] = nextMove;
            nextMove = (nextMove == O_CELL) ? X_CELL : O_CELL;
        }
    }
}




