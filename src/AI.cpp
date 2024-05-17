// #include "AI.h"
// #include "logic.h"
// #include <algorithm>

// AI::AI(char symbol) : playerSymbol(symbol), opponentSymbol((symbol == 'X') ? 'O' : 'X') {}

// void AI::makeMove(int board[20][20]) {
//     std::pair<int, int> bestMove = findBestMove(board);
//     board[bestMove.first][bestMove.second] = playerSymbol;
// }

// int AI::evaluateBoard(int board[20][20]) {
//     // Implement the logic to evaluate the board and return a score
//     // Positive score for playerSymbol, negative score for opponentSymbol
//     return 0; // Placeholder value
// }

// int AI::minimax(int board[20][20], int depth, bool isMax) {
//     int score = evaluateBoard(board);

//     // If maximizer has won the game, return evaluated score
//     if (score == 10)
//         return score - depth;

//     // If minimizer has won the game, return evaluated score
//     if (score == -10)
//         return score + depth;

//     // If there are no more moves and no winner, it's a tie
//     bool isMovesLeft = false;
//     for (int i = 0; i < 20; ++i) {
//         for (int j = 0; j < 20; ++j) {
//             if (board[i][j] == EMPTY_CELL) {
//                 isMovesLeft = true;
//                 break;
//             }
//         }
//     }
//     if (!isMovesLeft)
//         return 0;

//     // If this is maximizer's move
//     if (isMax) {
//         int best = -1000;

//         // Traverse all cells
//         for (int i = 0; i < 20; ++i) {
//             for (int j = 0; j < 20; ++j) {
//                 // Check if cell is empty
//                 if (board[i][j] == EMPTY_CELL) {
//                     // Make the move
//                     board[i][j] = playerSymbol;

//                     // Call minimax recursively and choose the maximum value
//                     best = std::max(best, minimax(board, depth + 1, !isMax));

//                     // Undo the move
//                     board[i][j] = EMPTY_CELL;
//                 }
//             }
//         }
//         return best;
//     } else {
//         // If this is minimizer's move
//         int best = 1000;

//         // Traverse all cells
//         for (int i = 0; i < 20; ++i) {
//             for (int j = 0; j < 20; ++j) {
//                 // Check if cell is empty
//                 if (board[i][j] == EMPTY_CELL) {
//                     // Make the move
//                     board[i][j] = opponentSymbol;

//                     // Call minimax recursively and choose the minimum value
//                     best = std::min(best, minimax(board, depth + 1, !isMax));

//                     // Undo the move
//                     board[i][j] = EMPTY_CELL;
//                 }
//             }
//         }
//         return best;
//     }
// }

// std::pair<int, int> AI::findBestMove(int board[20][20]) {
//     int bestVal = -1000;
//     std::pair<int, int> bestMove = {-1, -1};

//     // Traverse all cells, evaluate minimax function for all empty cells, and return the cell with optimal value
//     for (int i = 0; i < 20; ++i) {
//         for (int j = 0; j < 20; ++j) {
//             // Check if cell is empty
//             if (board[i][j] == EMPTY_CELL) {
//                 // Make the move
//                 board[i][j] = playerSymbol;

//                 // Compute evaluation function for this move
//                 int moveVal = minimax(board, 0, false);

//                 // Undo the move
//                 board[i][j] = EMPTY_CELL;

//                 // If the value of the current move is more than the best value, update bestMove
//                 if (moveVal > bestVal) {
//                     bestMove = {i, j};
//                     bestVal = moveVal;
//                 }
//             }
//         }
//     }
//     return bestMove;
// }
