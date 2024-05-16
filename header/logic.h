
#ifndef _LOGIC__H
#define _LOGIC__H

#include <chrono>
#include <random>
#include <cstring>

#include "graphics.h"

#define BOARD_SIZE 20
#define EMPTY_CELL ' '
#define O_CELL 'o'
#define X_CELL 'x'

class Graphics;

class TicTacToe {
private:

public:
    
    Uint32 gameTime;
    Uint32 startTime;
    Uint32 remainingTime;

    void startGame();
    void checkGameTime();
    void endGame();

    int board[BOARD_SIZE][BOARD_SIZE];
    int mines[BOARD_SIZE][BOARD_SIZE];
    bool flags[BOARD_SIZE][BOARD_SIZE];

    int currentPlayer;
    char nextMove = O_CELL;
    bool game_over = false;

    bool checkWin(char playerSymbol);
    bool checkLine(int startRow, int startCol, int dRow, int dCol, char playerSymbol);
    

    int healthX = 100;
    int healthO = 100;
    int scorePlayer1 = 0;
    int scorePlayer2 = 0;

    
    void placeMines(int mineCount);
    void displayDamageMessage(int damage);
    void updateScore(int player);
    

    int calculateDamage();
    std::string createMessageBasedOnDamage(int damage);

    Graphics& graphics;
    TicTacToe(Graphics& graphics);


    void init();
    void move(int row, int col);
    void placeFlags(int row, int col);
    bool showMines = false;



};

#endif




