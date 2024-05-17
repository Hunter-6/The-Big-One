// #include "SDL.h"
// #include "SDL_ttf.h"
// #include "Menu.h"
// #include <string>
// #include <iostream>
// #include "Game.h"

// Menu::Menu(SDL_Renderer* renderer) : renderer(renderer), selectedOption(0), font(nullptr) {
//     // Kiểm tra và khởi tạo TTF
//     if (TTF_WasInit() == 0 && TTF_Init() == -1) {
//         SDL_Log("Unable to initialize SDL_ttf: %s", TTF_GetError());
//         return;
//     }

//     // Khởi tạo font
//     const char* fontPath = "D:\\game study UET\\projects\\true-proj\\The-Big-One\\assets\\fonts\\Vermin Vibes 1989.ttf";
//     font = TTF_OpenFont(fontPath, 28);
//     if (!font) {
//         SDL_Log("Unable to load font: %s", TTF_GetError());
//         return;
//     }

//     // Khởi tạo SDL_Rects cho các nút
//     playRect = {100, 100, 200, 50}; // Vị trí 100, 100, chiều rộng 200, chiều cao 50
//     introRect = {100, 200, 200, 50};
//     quitRect = {100, 300, 200, 50};

//     // Cài đặt màu sắc cho văn bản
//     SDL_Color color = {255, 255, 255, 255}; // Màu trắng

//     // Tạo texture cho các nút
//     playTexture = createTextTexture("Play", font, color);
//     introTexture = createTextTexture("Introductions", font, color);
//     quitTexture = createTextTexture("Quit", font, color);
// }
// Menu::~Menu() {
//     if (font) {
//         TTF_CloseFont(font);
//     }
//     SDL_DestroyTexture(playTexture);
//     SDL_DestroyTexture(introTexture);
//     SDL_DestroyTexture(quitTexture);
// }

// void Menu::addOption(const std::string& text) {
//     options.push_back(text);
// }

// SDL_Texture* Menu::createTextTexture(const char* text, TTF_Font* font, SDL_Color color) {
//     SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
//     SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
//     SDL_FreeSurface(surface);
//     return texture;
// }

// void Menu::run() {
//     bool quit = false;
//     SDL_Event e;
//     bool showIntro = false; // Flag to control display of introduction screen

//     while (!quit) {
//         while (SDL_PollEvent(&e) != 0) {
//             if (e.type == SDL_QUIT) {
//                 quit = true;
//             } else if (e.type == SDL_MOUSEBUTTONDOWN) {
//                 int x = e.button.x, y = e.button.y;
//                 if (buttonPressed(x, y, playRect)) {
//                     // Start the game
//                     startGame();
//                 } else if (buttonPressed(x, y, introRect)) {
//                     showIntro = true;
//                 } else if (buttonPressed(x, y, quitRect)) {
//                     SDL_Event quit_event;
//                     quit_event.type = SDL_QUIT;
//                     SDL_PushEvent(&quit_event);
//                 }
//             }
//         }

//         SDL_RenderClear(renderer);
//         if (showIntro) {
//             displayIntroduction();
//         } else {
//             renderTexture(playTexture, 100, 100);
//             renderTexture(introTexture, 100, 200);
//             renderTexture(quitTexture, 100, 300);
//         }
//         SDL_RenderPresent(renderer);
//     }
// }

// bool Menu::buttonPressed(int x, int y, SDL_Rect rect) {
//     return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
// }

// void Menu::renderTexture(SDL_Texture* tex, int x, int y) {
//     SDL_Rect dst;
//     dst.x = x;
//     dst.y = y;
//     SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
//     SDL_RenderCopy(renderer, tex, NULL, &dst);
// }

// void Menu::render() {
//     SDL_Color color;
//     for (size_t i = 0; i < options.size(); ++i) {
//         if (i == selectedOption) {
//             color = {255, 0, 0, 255}; // Màu đỏ cho tùy chọn được chọn
//         } else {
//             color = {255, 255, 255, 255}; // Màu trắng cho các tùy chọn khác
//         }
//         drawText(options[i], 100, 100 + i * 50, color);
//     }
// }

// int Menu::handleEvent(SDL_Event& e) {
//     if (e.type == SDL_KEYDOWN) {
//         if (e.key.keysym.sym == SDLK_DOWN) {
//             selectedOption = (selectedOption + 1) % options.size();
//         } else if (e.key.keysym.sym == SDLK_UP) {
//             selectedOption = (selectedOption - 1 + options.size()) % options.size();
//         } else if (e.key.keysym.sym == SDLK_RETURN) {
//             return selectedOption;
//         }
//     }
//     return -1;
// }

// void Menu::drawText(const std::string& message, int x, int y, SDL_Color color) {
//     SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
//     if (surface == nullptr) {
//         SDL_Log("Failed to create surface: %s", TTF_GetError());
//         return;
//     }
//     SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
//     if (texture == nullptr) {
//         SDL_Log("Failed to create texture: %s", SDL_GetError());
//         SDL_FreeSurface(surface);
//         return;
//     }
//     SDL_Rect rect = {x, y, surface->w, surface->h};
//     SDL_RenderCopy(renderer, texture, nullptr, &rect);
//     SDL_DestroyTexture(texture);
//     SDL_FreeSurface(surface);
// }

// void Menu::startGame() {
//     SDL_HideWindow(window);
//     Game game(renderer);
//     game.init();
//     game.run();
//     SDL_ShowWindow(window);
// }

// void Menu::displayIntroduction() {
//     // Display the introduction screen with game rules
//     SDL_RenderClear(renderer);
//     std::string introText = "Welcome to the game. Here are the rules...";
//     SDL_Texture* introTextTexture = createTextTexture(introText.c_str(), TTF_OpenFont("D:\\game study UET\\projects\\true-proj\\The-Big-One\\assets\\fonts\\Vermin Vibes 1989.ttf", 24), {255, 255, 255, 255});
//     renderTexture(introTextTexture, 50, 50); // Adjust position as needed
//     SDL_DestroyTexture(introTextTexture);
// }
