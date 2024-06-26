#include "graphics.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
// #include "defs.h"
#include "logic.h"
#include <SDL_syswm.h>

void Graphics::initSDL()
{
    SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Init();
    font = TTF_OpenFont("D:\\game study UET\\projects\\true-proj\\The-Big-One\\assets\\fonts\\Vermin Vibes 1989.ttf", 24);
}

SDL_Texture *Graphics::loadTexture(const char *filePath)
{
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(filePath);
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", filePath, IMG_GetError());
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void Graphics::init()
{
    initSDL();
    cellEmpty = loadTexture("img//cell_empty.png");
    cellX = loadTexture("img//cell_x.png");
    cellO = loadTexture("img//cell_o.png");
    cellMine = loadTexture("img//cell_mines.png"); 
    cellFlag = loadTexture("img//cell_flags.png");
}

void Graphics::renderTexture(SDL_Texture *texture, int x, int y)
{

    // Centering the board on the screen
    int boardWidth = BOARD_SIZE * CELL_SIZE;
    int boardHeight = BOARD_SIZE * CELL_SIZE;
    int boardX = (SCREEN_WIDTH - boardWidth) / 2;
    int boardY = (SCREEN_HEIGHT - boardHeight) / 2 + 50; // Offset by 50 pixels from the top for health info
    SDL_Rect renderQuad = {boardX + x, boardY + y, CELL_SIZE, CELL_SIZE};

    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}

std::string formatTime(Uint32 timeInMilliseconds) {
    Uint32 totalSeconds = timeInMilliseconds / 1000;
    Uint32 seconds = totalSeconds % 60;
    Uint32 minutes = totalSeconds / 60;
    char buffer[10];
    sprintf(buffer, "%02u:%02u", minutes, seconds);
    return std::string(buffer);
}


void Graphics::render( TicTacToe &game)
{
    SDL_RenderClear(renderer);
    // for (int i = 0; i < BOARD_SIZE; i++)
    //     for (int j = 0; j < BOARD_SIZE; j++)
    //     {
    //         int x = BOARD_X + j * CELL_SIZE;
    //         int y = BOARD_Y + i * CELL_SIZE;
    //         SDL_Texture *currentTexture = cellEmpty;
    //         if (game.mines[i][j] && game.game_over) // Assuming game_over is a status flag
    //             currentTexture = cellMine;
    //         else if (game.showMines && game.mines[i][j])
    //             currentTexture = cellMine;
    //         else
    //             switch (game.board[i][j])
    //             {
    //             case EMPTY_CELL:
    //                 currentTexture = cellEmpty;
    //                 break;
    //             case X_CELL:
    //                 currentTexture = cellX;
    //                 break;
    //             case O_CELL:
    //                 currentTexture = cellO;
    //                 break;
    //             }
    //         renderTexture(currentTexture, x, y);
    //     }

    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            int x = BOARD_X + j * CELL_SIZE;
            int y = BOARD_Y + i * CELL_SIZE;

            SDL_Texture* textureToUse = game.board[i][j] == EMPTY_CELL ? cellEmpty : ( game.board[i][j] == X_CELL ? cellX : cellO);
            if (game.showMines && game.mines[i][j]) {
                textureToUse = cellMine;

            } else if ( game.flags[i][j]) {
                textureToUse = cellFlag;
            }

            renderTexture(textureToUse, x, y);

            // if (game.flags[i][j]){
            //     renderTexture(cellFlag,x,y);
            // }
        }
    }

    // Display health information using SDL_ttf
    // char healthInfoX[100];
    // sprintf(healthInfoX, "Health X: %d", game.healthX);
    // SDL_Color textColor = {255, 255, 255}; // White color
    // SDL_Surface *textSurfaceX = TTF_RenderText_Solid(font, healthInfoX, textColor);
    // SDL_Texture *textTextureX = SDL_CreateTextureFromSurface(renderer, textSurfaceX);
    // SDL_Rect textRectX = {10, 10, 200, 30}; // Adjust position and size accordingly
    // SDL_RenderCopy(renderer, textTextureX, NULL, &textRectX);
    // SDL_DestroyTexture(textTextureX);
    // SDL_FreeSurface(textSurfaceX);

    // char healthInfoO[100];
    // sprintf(healthInfoO, "Health O: %d", game.healthO);
    // SDL_Surface *textSurfaceO = TTF_RenderText_Solid(font, healthInfoO, textColor);
    // SDL_Texture *textTextureO = SDL_CreateTextureFromSurface(renderer, textSurfaceO);
    // SDL_Rect textRectO = {SCREEN_WIDTH - 210, 10, 200, 30}; // Adjust position for player O on the top right
    // SDL_RenderCopy(renderer, textTextureO, NULL, &textRectO);
    // SDL_DestroyTexture(textTextureO);
    // SDL_FreeSurface(textSurfaceO);

    // //score
    // char scoreInfoX[0], scoreInfoO[0];
    // sprintf(scoreInfoX, "Score X: %d", game.scorePlayer1);
    // sprintf(scoreInfoO, "Score O: %d", game.scorePlayer2);
    // renderText(scoreInfoX, 10, 50, textColor);  // Adjust Y to be below Health X
    // renderText(scoreInfoO, SCREEN_WIDTH - 210, 50, textColor);  // Adjust Y to be below Health O

    // // Calculate and display remaining time
    // Uint32 remainingTime = (game.gameTime - (SDL_GetTicks() - game.startTime)) / 1000;  // in seconds
    // char timeText[100];
    // sprintf(timeText, "Time: %d", remainingTime);
    // renderText(timeText, SCREEN_WIDTH / 2 - 50, 10, textColor);  // Middle top of the screen

    // Uint32 elapsed = SDL_GetTicks() - game.startTime;
    // Uint32 remainingTime = (elapsed < game.gameTime) ? (game.gameTime - elapsed) : 0;
    // std::string timeText = "Time: " + formatTime(remainingTime);

    //tối ưu hoá 
    SDL_Color textColor = {255, 255, 255}; // Màu trắng
    SDL_Color textColor1 = {255, 0, 0, 244};
    SDL_Color textColor2 = {0, 0, 255, 255};
    std::string healthInfoX = "Health X: " + std::to_string(game.healthX);
    std::string healthInfoO = "Health O: " + std::to_string(game.healthO);
    std::string scoreInfoX = "Score X: " + std::to_string(game.scorePlayer1);
    std::string scoreInfoO = "Score O: " + std::to_string(game.scorePlayer2);
    std::string timeText = "Time: " + formatTime(SDL_GetTicks() - game.startTime);


    renderText(healthInfoX, 10, 50, textColor); 
    renderText(healthInfoO, SCREEN_WIDTH - 210, 50, textColor);
    renderText(scoreInfoX, 10, 80, textColor1);
    renderText(scoreInfoO, SCREEN_WIDTH - 210, 80, textColor1);
    renderText(timeText, SCREEN_WIDTH / 2 - 50, 20, textColor2);

    presentScene();
}

void Graphics::renderText(const std::string &message, int x, int y, SDL_Color color)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, message.c_str(), color);
    if (textSurface == NULL){
        std::cerr << "Unable to render text texture: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        std::cerr << "Unable to create texture: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    // TTF_CloseFont(font);
    // TTF_Quit();
}

void Graphics::presentScene()
{
    SDL_RenderPresent(renderer);
}

void Graphics::quit()
{
    // Destroy textures
    SDL_DestroyTexture(cellEmpty);
    SDL_DestroyTexture(cellX);
    SDL_DestroyTexture(cellO);
    SDL_DestroyTexture(cellMine);

    // Destroy renderer and window

    TTF_CloseFont(font); // Close the font before quitting
    SDL_DestroyRenderer(renderer);
    TTF_Quit(); // Quit SDL_ttf

    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();
}

SDL_Renderer *Graphics::getRenderer()
{
    return renderer;
}
SDL_Texture *Graphics::getMineTexture()
{
    return cellMine; // Assuming cellMine is the texture for mines
}