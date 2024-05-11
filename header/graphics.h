
#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_ttf.h>
#include "defs.h"
#include "logic.h"

struct Graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Texture *cellEmpty, *cellX, *cellO, *cellMine;  // Add texture for mine
    TTF_Font *font;

    void initSDL() {
        SDL_Init(SDL_INIT_VIDEO);  // Initialize SDL2
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        renderer = 
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        TTF_Init(); // Initialize SDL_ttf
        font = TTF_OpenFont("D:\\game study UET\\projects\\true-proj\\The-Big-One\\assets\\fonts\\Vermin Vibes 1989.ttf", 24);
    }

    SDL_Texture* loadTexture(const char* filePath) {
        SDL_Texture* newTexture = NULL;
        SDL_Surface* loadedSurface = IMG_Load(filePath);
        if (loadedSurface == NULL) {
            printf("Unable to load image %s! SDL_image Error: %s\n", filePath, IMG_GetError());
        } else {
            newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
            SDL_FreeSurface(loadedSurface);
        }
        return newTexture;
    }

    void init() {
        initSDL();
        cellEmpty = loadTexture("img//cell_empty.png");
        cellX = loadTexture("img//cell_x.png");
        cellO = loadTexture("img//cell_o.png");
        cellMine = loadTexture("img//cell_mines.png");  // Load mine texture
    }

    void renderTexture(SDL_Texture* texture, int x, int y) {
        
        // Centering the board on the screen
        int boardWidth = BOARD_SIZE * CELL_SIZE;
        int boardHeight = BOARD_SIZE * CELL_SIZE;
        int boardX = (SCREEN_WIDTH - boardWidth) / 2;
        int boardY = (SCREEN_HEIGHT - boardHeight) / 2 + 50; // Offset by 50 pixels from the top for health info
        SDL_Rect renderQuad = {boardX + x, boardY + y, CELL_SIZE, CELL_SIZE};
        
            SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
    }

    void render(const Tictactoe& game) {
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++) {
                int x = BOARD_X + j * CELL_SIZE;
                int y = BOARD_Y + i * CELL_SIZE;
                SDL_Texture* currentTexture = cellEmpty;
                if (game.mines[i][j] && game.game_over)  // Assuming game_over is a status flag
                    currentTexture = cellMine;
                else
                    if (game.showMines && game.mines[i][j]) currentTexture = cellMine;
                else switch (game.board[i][j]) {
                        case EMPTY_CELL: currentTexture = cellEmpty; break;
                        case X_CELL: currentTexture = cellX; break;
                        case O_CELL: currentTexture = cellO; break;
                    }
                renderTexture(currentTexture, x, y);
            }
        
 
    
    // Display health information using SDL_ttf
    char healthInfoX[100];
    sprintf(healthInfoX, "Health X: %d", game.healthX);
    SDL_Color textColor = {255, 255, 255};  // White color
    SDL_Surface* textSurfaceX = TTF_RenderText_Solid(font, healthInfoX, textColor);
    SDL_Texture* textTextureX = SDL_CreateTextureFromSurface(renderer, textSurfaceX);
    SDL_Rect textRectX = {10, 10, 200, 30};  // Adjust position and size accordingly
    SDL_RenderCopy(renderer, textTextureX, NULL, &textRectX);
    SDL_DestroyTexture(textTextureX);
    SDL_FreeSurface(textSurfaceX);

    char healthInfoO[100];
    sprintf(healthInfoO, "Health O: %d", game.healthO);
    SDL_Surface* textSurfaceO = TTF_RenderText_Solid(font, healthInfoO, textColor);
    SDL_Texture* textTextureO = SDL_CreateTextureFromSurface(renderer, textSurfaceO);
    SDL_Rect textRectO = {SCREEN_WIDTH - 210, 10, 200, 30}; // Adjust position for player O on the top right
    SDL_RenderCopy(renderer, textTextureO, NULL, &textRectO);
    SDL_DestroyTexture(textTextureO);
    SDL_FreeSurface(textSurfaceO);


    
    presentScene();
    
    
    }

    void renderText(const std::string& text, int x, int y, SDL_Color color) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    void presentScene() {
        SDL_RenderPresent(renderer);
    }

    void quit() {
        // Destroy textures
        SDL_DestroyTexture(cellEmpty);
        SDL_DestroyTexture(cellX);
        SDL_DestroyTexture(cellO);
        SDL_DestroyTexture(cellMine);  // If you have a texture for mines

        // Destroy renderer and window
        
        TTF_CloseFont(font); // Close the font before quitting
        SDL_DestroyRenderer(renderer);
        TTF_Quit(); // Quit SDL_ttf
        
        SDL_DestroyWindow(window);

        // Quit SDL subsystems
        SDL_Quit();
    }

};



#endif
