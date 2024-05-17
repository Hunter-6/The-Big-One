// #include "Game.h"

// Game::Game(SDL_Renderer* renderer) : window(window), renderer(renderer), ai(nullptr), menu(nullptr), running(false), gameOver(false), logic(graphics) {
    
// }

// Game::~Game() {
//     if (ai) delete ai;
//     if (menu) delete menu;
//     if (renderer) SDL_DestroyRenderer(renderer);
//     if (window) SDL_DestroyWindow(window);
//     TTF_Quit();
//     SDL_Quit();
// }

// bool Game::init() {
//     if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
//     if (TTF_Init() == -1) return false;
//     graphics.init();
//     ai = new AI('O');
//     menu = new Menu(renderer);
//     menu->addOption("Play");
//     menu->addOption("Quit");
//     reset();
//     return true;
// }

// void Game::run() {
//     running = true;
//     while (running) {
//         handleEvents();
//         update();
//         render();
//     }
// }

// void Game::handleEvents() {
//     SDL_Event e;
//     while (SDL_PollEvent(&e) != 0) {
//         if (e.type == SDL_QUIT) {
//             running = false;
//         }

//         int option = menu->handleEvent(e);
//         if (option == 0) { // Play
//             reset();
//         } else if (option == 1) { // Quit
//             running = false;
//         }

//         if (e.type == SDL_MOUSEBUTTONDOWN && !gameOver) {
//             int x = e.button.x / (800 / BOARD_SIZE);
//             int y = e.button.y / (600 / BOARD_SIZE);
//             logic.move(x, y);
//             if (logic.checkWin(logic.nextMove)) gameOver = true;
//             logic.nextMove = (logic.nextMove == O_CELL) ? X_CELL : O_CELL;
//         }
//     }
// }

// void Game::update() {
//     if (logic.nextMove == O_CELL && !gameOver) {
//         ai->makeMove(logic.board);
//         if (logic.checkWin(O_CELL)) gameOver = true;
//         logic.nextMove = X_CELL;
//     }
// }

// void Game::render() {
//     graphics.clear();
//     menu->render(); // Render the menu
//     graphics.render(logic); // Sử dụng hàm render từ Graphics để vẽ bảng
//     graphics.presentScene();
// }

// void Game::reset() {
//     logic.init();
//     gameOver = false;
//     running = true;
// }
