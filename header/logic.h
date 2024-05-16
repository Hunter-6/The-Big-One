
#ifndef _LOGIC__H
#define _LOGIC__H

#include <chrono>
#include <random>
#include <cstring>

// struct Graphics;

#define BOARD_SIZE 20
#define EMPTY_CELL ' '
#define O_CELL 'o'
#define X_CELL 'x'

struct TicTacToe {
    int board[BOARD_SIZE][BOARD_SIZE];
    int mines[BOARD_SIZE][BOARD_SIZE];
    bool flags[BOARD_SIZE][BOARD_SIZE];

    // Graphics& graphics;
    // TicTacToe(Graphics& graphics);

    int currentPlayer;
    char nextMove = O_CELL;
    bool game_over = false;
    bool showMines = false;

    int healthX = 100;
    int healthO = 100;


    void init();
    void move(int row, int col);
    void placeMines(int mineCount);
    void placeFlags(int row, int col);
    bool checkWin();
    // void showMines(SDL_Renderer* renderer, SDL_Texture* cellMineTexture);
};

#endif



void showMines(SDL_Renderer* renderer, SDL_Texture* mineTexture);  // Add declaration
