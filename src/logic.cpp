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

TicTacToe::TicTacToe(Graphics& graphics) : graphics(graphics) {

    init();  
}


// void TicTacToe::move(int row, int column) {
//     if (!game_over && board[row][column] == EMPTY_CELL) {
//         if (mines[row][column]) {
//             std::random_device rd;
//             static std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
//             std::uniform_int_distribution<> dis(0, 5);
//             int damage = dis(rng);

//             // Apply the damage
//             if (nextMove == O_CELL) {
//                 healthO -= damage;
//                 board[row][column] = X_CELL;
//             } else {
//                 healthX -= damage;
//                 board[row][column] = O_CELL;
//             }

//             std::string message;
//             if (damage == 0) {
//                 message = "Gotcha!!";
//             } else if (damage == 1 || damage == 2) {
//                 message = "Tiny Boom...";
//             } else if (damage == 3 || damage == 4) {
//                 message = "Good BOOM~";
//             } else if (damage == 5) {
//                 message = "HASABULLA! BOOM BOOM BOOM!!!";
//             }
//             std::cout << message << std::endl;  
//             // SDL_Color textColor = {255, 255, 0};
//             // graphics.renderText(message, 100, 100, textColor);

//             nextMove = (nextMove == O_CELL) ? X_CELL : O_CELL;  
//         } else {
//             board[row][column] = nextMove;
//             nextMove = (nextMove == O_CELL) ? X_CELL : O_CELL;
//         }
//     }
// }

void TicTacToe::move(int row, int column){

    if (!game_over && mines[row][column]){
        int damage = calculateDamage();
        if (currentPlayer == 1){
            healthO -= damage;
        } else {
            healthX -= damage;
        }



        std::string message = createMessageBasedOnDamage(damage);
        SDL_Color color = {255,255,255};
        graphics.renderText(message, 100, 100, color);

        currentPlayer = (currentPlayer == 1 ? 2 : 1);
    } else if (board[row][column] == EMPTY_CELL){
        char currentPlayerSymbol = (currentPlayer == 1 ? X_CELL : O_CELL);
        board[row][column] = currentPlayerSymbol;
        if (checkWin(currentPlayerSymbol)){
            updateScore(currentPlayer);
        }
        currentPlayer = (currentPlayer == 1 ? 2 : 1); 
    }
}

int TicTacToe::calculateDamage(){
    std::uniform_int_distribution<int> distribution(0,5);
    std::random_device rd;
    std::mt19937 engine(rd());
    return distribution(engine);
}

std::string TicTacToe::createMessageBasedOnDamage(int damage){
    switch(damage){
        case 0: return "Lucky asf! I'm just kidding bozo!";
        case 1: case 2: return "Hey! Just a little ticks with ya, right? :D";
        case 3: case 4: return "Oof! That must be hurt a lot! AND I LIKE IT!!";
        case 5: return "HAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHA";
        default: return "Do we even have this kind of boombs??";
    }
}

void TicTacToe::displayDamageMessage(int damage) {
    std::string message = createMessageBasedOnDamage(damage);
    SDL_Color color = {255, 255, 255};  
    int textX = SCREEN_WIDTH / 2;
    int textY = 50;                    

    graphics.renderText(message, textX, textY, color);
}

bool TicTacToe::checkWin(char playerSymbol) {
    // Kiểm tra hàng ngang, dọc và đường chéo cho playerSymbol
    for (int i = 0; i < BOARD_SIZE; i++) {
        // Kiểm tra hàng ngang
        if (checkLine(i, 0, 0, 1, playerSymbol) ||  // Kiểm tra từng hàng
            checkLine(0, i, 1, 0, playerSymbol) ||  // Kiểm tra từng cột
            checkLine(0, 0, 1, 1, playerSymbol) ||  // Kiểm tra đường chéo chính
            checkLine(0, BOARD_SIZE - 1, 1, -1, playerSymbol)) {  // Kiểm tra đường chéo phụ
            return true;
        }
    }
    return false;
}


bool TicTacToe::checkLine(int startRow, int startCol, int dRow, int dCol, char playerSymbol) {
    int count = 0;
    for (int i = 0; i < 5; i++) {  // Giả sử bạn cần 5 quân liên tiếp để thắng
        int r = startRow + i * dRow;
        int c = startCol + i * dCol;
        if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == playerSymbol) {
            count++;
        } else {
            break;
        }
    }
    return count == 5;
}

void TicTacToe::updateScore(int player) {
    if (player == 1) {
        scorePlayer1 += 2;
    } else {
        scorePlayer2 += 2;
    }
}

void TicTacToe::endGame() {
    int finalScorePlayer1 = scorePlayer1 * healthO;
    int finalScorePlayer2 = scorePlayer2 * healthX;

    std::cout << "Game Over!\n";
    std::cout << "Player 1 Score: " << finalScorePlayer1 << "\n";
    std::cout << "Player 2 Score: " << finalScorePlayer2 << "\n";

    if (finalScorePlayer1 > finalScorePlayer2) {
        std::cout << "Player 1 wins!\n";
    } else if (finalScorePlayer1 < finalScorePlayer2) {
        std::cout << "Player 2 wins!\n";
    } else {
        std::cout << "It's a draw!\n";
    }
}

void TicTacToe::startGame() {
    startTime = SDL_GetTicks();  // Lưu thời điểm bắt đầu trò chơi
    gameTime = 900000;  // Thiết lập thời gian trò chơi là 15 phút
    remainingTime = gameTime;
}

void TicTacToe::checkGameTime() {
    Uint32 currentTime = SDL_GetTicks();
    Uint32 elapsedTime = currentTime - startTime;
    if (elapsedTime >= gameTime) {
        endGame();
    } else {
        remainingTime = gameTime - elapsedTime; 
    }
}

