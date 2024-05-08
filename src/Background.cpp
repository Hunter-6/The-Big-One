#include "Background.h"
#include <string>
#include <iostream>

Background::Background(SDL_Renderer* renderer, const char* folderPath, int numberOfLayers, int screenWidth, int screenHeight, int layerHeight) 
    : m_renderer(renderer), m_numberOfLayers(numberOfLayers), m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_layerHeight(layerHeight) {
    // Tải các texture từ các tệp hình ảnh trong thư mục
    std::string basePath = folderPath;
    SDL_Surface* surface = nullptr;

    for (int i = 0; i < numberOfLayers; i++) {
        // Tạo đường dẫn đầy đủ đến tệp hình ảnh
        std::string imagePath = basePath + "/Layer_" + std::to_string(i) + ".png";
        
        // Tải hình ảnh từ tệp
        surface = IMG_Load(imagePath.c_str());
        if (surface == nullptr) {
            std::cerr << "Unable to load image " << imagePath << "! SDL_image Error: " << IMG_GetError() << std::endl;
            break;
        }

        // Tạo texture từ surface và thêm vào vector layers
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr) {
            std::cerr << "Unable to create texture from " << imagePath << "! SDL Error: " << SDL_GetError() << std::endl;
            break;
        }

        m_layers.push_back(texture);

        // Giải phóng surface
        SDL_FreeSurface(surface);
    }
}

Background::~Background() {
    // Hủy bỏ các texture
    for (auto& layer : m_layers) {
        SDL_DestroyTexture(layer);
    }
}

void Background::render() {
    // Vẽ các layer background lên màn hình
    int yPos = 0; // Vị trí y ban đầu
    for (auto& layer : m_layers) {
        // Tạo rect để vẽ texture
        SDL_Rect destRect = {0, yPos, m_screenWidth, m_screenHeight};
        
        // Vẽ layer lên màn hình
        SDL_RenderCopy(m_renderer, layer, NULL, &destRect);

        // Tăng vị trí y cho layer tiếp theo
        yPos += m_layerHeight; // layerHeight là chiều cao của mỗi layer (cố định hoặc biến đổi tùy thuộc vào thiết kế)
    }
}
