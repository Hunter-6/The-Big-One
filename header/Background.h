#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class Background {
public:
    Background(SDL_Renderer* renderer, const char* folderPath, int numberOfLayers, int screenWidth, int screenHeight, int layerHeight);
    ~Background();

    void render(); // Vẽ background và nền đất lên màn hình

private:
    SDL_Renderer* m_renderer; // Renderer
    std::vector<SDL_Texture*> m_layers;
    int m_numberOfLayers;
    int m_screenWidth;
    int m_screenHeight;
    int m_layerHeight;

};

#endif // BACKGROUND_H
