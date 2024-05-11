#ifndef _LOGIC__H
#define _LOGIC__H


#include <chrono>
#include <random>
#include <cstring>
#define BOARD_SIZE 20
#define EMPTY_CELL ' '
#define O_CELL 'o'
#define X_CELL 'x'



// Tic-tac-toe game logic

struct Tictactoe {
    char board[BOARD_SIZE][BOARD_SIZE];
    bool mines[BOARD_SIZE][BOARD_SIZE]; // Adding mines array
    char nextMove = O_CELL;
    bool game_over = false;  // Track if the game is over
    bool showMines =false;
    int healthX = 100;
    int healthO = 100;

    void init() {
        std::memset(mines, false, sizeof(mines));  // Initialize all cells as no mines
        placeMines(35);  // Randomly place 30 mines
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++) board[i][j] = EMPTY_CELL;
    }

    
void placeMines(int mineCount) {
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
    
    void move(int row, int column) {
        if (row >= 0 && row < BOARD_SIZE && column >= 0 && column < BOARD_SIZE) {
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
                std::cout << message << std::endl;  // Output the message to the console

                nextMove = (nextMove == O_CELL) ? X_CELL : O_CELL;  // Toggle turn after mine activation
            } else {
                board[row][column] = nextMove;
                nextMove = (nextMove == O_CELL) ? X_CELL : O_CELL;
            }
        }
    }
};


#endif
