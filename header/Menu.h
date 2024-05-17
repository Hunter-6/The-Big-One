// #ifndef MENU_H
// #define MENU_H

// #include <vector>
// #include <string>
// #include <SDL.h>
// #include <SDL_ttf.h>

// class Menu {
// public:
//     Menu(SDL_Renderer* renderer); // Constructor accepting SDL_Renderer*
//     ~Menu();

//     void addOption(const std::string& text);
//     SDL_Texture* createTextTexture(const char* text, TTF_Font* font, SDL_Color color);
//     void run();
//     bool buttonPressed(int x, int y, SDL_Rect rect);
//     void renderTexture(SDL_Texture* tex, int x, int y);
//     void render();
//     int handleEvent(SDL_Event& e);
//     void drawText(const std::string& message, int x, int y, SDL_Color color);
//     void startGame();
//     void displayIntroduction();

// private:
//     SDL_Renderer* renderer;
//     SDL_Window* window;
//     TTF_Font* font;
//     std::vector<std::string> options;
//     int selectedOption;

//     SDL_Rect playRect;
//     SDL_Rect introRect;
//     SDL_Rect quitRect;

//     SDL_Texture* playTexture;
//     SDL_Texture* introTexture;
//     SDL_Texture* quitTexture;
// };

// #endif
