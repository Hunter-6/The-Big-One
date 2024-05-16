
#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "defs.h"
#include "logic.h"
#include <string>
#include <iostream>

class TicTacToe;

struct Graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Texture *cellEmpty, *cellX, *cellO, *cellMine, *cellFlag;
    TTF_Font *font;

    void initSDL();
    // void renderMessage(const char* message, SDL_Color color, int x, int y);
    void init();
    void renderTexture(SDL_Texture* texture, int x, int y);
    void render( TicTacToe& game);
    void renderText(const std::string& message, int x, int y, SDL_Color color);
    void presentScene();
    SDL_Texture* loadTexture(const char* filePath);
    void quit();
    SDL_Renderer* getRenderer();
    SDL_Texture* getMineTexture();
    
    void render();
};

#endif



